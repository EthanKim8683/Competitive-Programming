package server

import (
	"context"
	"fmt"
	"net"
	"sync"
	"time"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/config"
	browserservicev1 "github.com/EthanKim8683/Competitive-Programming/Utility/internal/gen/browserservice/v1"
	"golang.org/x/sync/errgroup"
	"google.golang.org/grpc"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
)

type Server struct {
	browserservicev1.UnimplementedBrowserServiceServer

	ctx context.Context
	cfg config.BrowserConfig

	browser *browser

	mu    sync.Mutex
	holds int
}

func (s *Server) hold(ctx context.Context) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	if s.holds == 0 {
		if err := s.browser.launch(); err != nil {
			return err
		}
	}
	s.holds++

	context.AfterFunc(ctx, func() {
		s.mu.Lock()
		defer s.mu.Unlock()

		if s.holds == 1 {
			s.browser.kill()
		}
		s.holds--
	})

	return nil
}

func (s *Server) Session(req *browserservicev1.SessionRequest, stream browserservicev1.BrowserService_SessionServer) error {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	if err := s.hold(ctx); err != nil {
		return status.Errorf(codes.Internal, "failed to launch browser: %v", err)
	}

	controlURL, err := s.browser.controlURL()
	if err != nil {
		return status.Errorf(codes.Internal, "failed to get browser control URL: %v", err)
	}

	if err := stream.Send(&browserservicev1.SessionResponse{
		ControlUrl: controlURL,
	}); err != nil {
		return status.Errorf(codes.Internal, "failed to send response: %v", err)
	}

	select {
	case <-stream.Context().Done():
	case <-s.ctx.Done():
		return nil
	}

	if keepAlive := req.GetKeepAlive(); keepAlive != nil {
		<-time.After(time.Duration(keepAlive.GetTimeoutMs()) * time.Millisecond)
	}

	return nil
}

func (s *Server) Run() error {
	grpcServer := grpc.NewServer()
	browserservicev1.RegisterBrowserServiceServer(grpcServer, s)

	lis, err := net.Listen("tcp", fmt.Sprintf("127.0.0.1:%d", s.cfg.GRPCPort))
	if err != nil {
		return err
	}
	defer lis.Close()

	g, ctx := errgroup.WithContext(s.ctx)
	g.Go(func() error {
		err := grpcServer.Serve(lis)
		if ctx.Err() != nil {
			return nil
		}
		return err
	})
	g.Go(func() error {
		<-ctx.Done()
		grpcServer.GracefulStop()
		return nil
	})
	return g.Wait()
}

func NewServer(ctx context.Context, cfg config.BrowserConfig) *Server {
	s := &Server{
		ctx: ctx,
		cfg: cfg,

		browser: newBrowser(cfg),
	}
	return s
}

var _ browserservicev1.BrowserServiceServer = &Server{}
