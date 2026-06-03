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

	browser    *browser
	refCounter *refCounter
}

func (s *Server) Acquire(_ context.Context, req *browserservicev1.AcquireRequest) (*browserservicev1.AcquireResponse, error) {
	release, err := s.refCounter.acquire()
	if err != nil {
		return nil, status.Error(codes.Internal, err.Error())
	}

	var once sync.Once
	releaseOnce := func() { once.Do(release) }
	time.AfterFunc(time.Duration(req.TtlMs)*time.Millisecond, releaseOnce)
	context.AfterFunc(s.ctx, releaseOnce)

	return &browserservicev1.AcquireResponse{}, nil
}

func (s *Server) ControlURL(_ context.Context, _ *browserservicev1.ControlURLRequest) (*browserservicev1.ControlURLResponse, error) {
	release, err := s.refCounter.acquire()
	if err != nil {
		return nil, status.Error(codes.Internal, err.Error())
	}
	defer release()

	wsURL, err := s.browser.controlURL()
	if err != nil {
		return nil, status.Error(codes.FailedPrecondition, err.Error())
	}
	return &browserservicev1.ControlURLResponse{ControlUrl: wsURL}, nil
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
		if err := grpcServer.Serve(lis); err != nil && ctx.Err() == nil {
			return err
		}
		return nil
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
	}
	s.browser = newBrowser(cfg)
	s.refCounter = newRefCounter(s.browser)
	return s
}

var _ browserservicev1.BrowserServiceServer = &Server{}
