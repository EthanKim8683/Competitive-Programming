package server

import (
	"context"
	"fmt"
	"net"
	"time"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/config"
	browserservicev1 "github.com/EthanKim8683/Competitive-Programming/Utility/internal/gen/browserservice/v1"
	"google.golang.org/grpc"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
)

type Server struct {
	browserservicev1.UnimplementedBrowserServiceServer

	cfg config.BrowserConfig

	acquire chan error
	release chan struct{}

	browser *browser
}

func (s *Server) Session(req *browserservicev1.SessionRequest, stream browserservicev1.BrowserService_SessionServer) error {
	if err := <-s.acquire; err != nil {
		return status.Errorf(codes.Internal, "session: %v", err)
	}
	defer func() {
		s.release <- struct{}{}
	}()

	controlURL, err := s.browser.controlURL()
	if err != nil {
		return status.Errorf(codes.Internal, "session: %v", err)
	}

	if err := stream.Send(&browserservicev1.SessionResponse{
		ControlUrl: controlURL,
	}); err != nil {
		return status.Errorf(codes.Internal, "session: %v", err)
	}

	<-stream.Context().Done()
	if keepAlive := req.GetKeepAlive(); keepAlive != nil {
		<-time.After(time.Duration(keepAlive.GetTimeoutMs()) * time.Millisecond)
	}

	return status.FromContextError(stream.Context().Err()).Err()
}

func (s *Server) Serve(ctx context.Context) error {
	lis, err := net.Listen("tcp", fmt.Sprintf("127.0.0.1:%d", s.cfg.GRPCPort))
	if err != nil {
		return fmt.Errorf("could not listen on port %d: %w", s.cfg.GRPCPort, err)
	}
	defer lis.Close()

	grpcServer := grpc.NewServer()
	browserservicev1.RegisterBrowserServiceServer(grpcServer, s)

	go func() {
		<-ctx.Done()
		grpcServer.GracefulStop()
	}()

	stop := make(chan struct{})
	defer close(stop)
	go func() {
		count := 0
		for {
			select {
			case s.acquire <- func() error {
				if count == 0 {
					if err := s.browser.launch(ctx); err != nil {
						return err
					}
				}
				count++
				return nil
			}():
			case <-s.release:
				count--
				if count == 0 {
					s.browser.kill()
				}
			case <-stop:
				return
			}
		}
	}()

	if err := grpcServer.Serve(lis); ctx.Err() == nil {
		return fmt.Errorf("could not serve gRPC server: %w", err)
	}
	return nil
}

func NewServer(cfg config.BrowserConfig) *Server {
	return &Server{
		cfg: cfg,

		acquire: make(chan error),
		release: make(chan struct{}),

		browser: newBrowser(cfg),
	}
}

var _ browserservicev1.BrowserServiceServer = &Server{}
