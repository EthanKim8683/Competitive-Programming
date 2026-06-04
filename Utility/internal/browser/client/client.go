package client

import (
	"context"
	"errors"
	"fmt"
	"time"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/config"
	browserservicev1 "github.com/EthanKim8683/Competitive-Programming/Utility/internal/gen/browserservice/v1"
	"google.golang.org/grpc"
	"google.golang.org/grpc/connectivity"
	"google.golang.org/grpc/credentials/insecure"
)

type Client struct {
	conn *grpc.ClientConn
	svc  browserservicev1.BrowserServiceClient
}

func Dial(ctx context.Context, cfg config.BrowserConfig, opts ...grpc.DialOption) (*Client, error) {
	opts = append([]grpc.DialOption{
		grpc.WithTransportCredentials(insecure.NewCredentials()),
	}, opts...)
	conn, err := grpc.NewClient(fmt.Sprintf("127.0.0.1:%d", cfg.GRPCPort), opts...)
	if err != nil {
		return nil, err
	}

	conn.Connect()
	for state := conn.GetState(); state != connectivity.Ready; state = conn.GetState() {
		if state == connectivity.Shutdown {
			return nil, errors.New("server shutdown")
		}

		if !conn.WaitForStateChange(ctx, state) {
			return nil, ctx.Err()
		}
	}

	return &Client{
		conn: conn,
		svc:  browserservicev1.NewBrowserServiceClient(conn),
	}, nil
}

func (c *Client) Close() error {
	if c.conn == nil {
		return nil
	}

	defer func() {
		c.conn = nil
		c.svc = nil
	}()

	return c.conn.Close()
}

type SessionOption func(*browserservicev1.SessionRequest)

func WithKeepAlive(timeout time.Duration) SessionOption {
	return func(req *browserservicev1.SessionRequest) {
		req.KeepAlive = &browserservicev1.SessionRequest_KeepAlive{
			TimeoutMs: uint32(timeout.Milliseconds()),
		}
	}
}

type Session struct {
	controlURL string
	cancel     context.CancelFunc
}

func (s *Session) ControlURL() string {
	return s.controlURL
}

func (s *Session) Close() {
	s.cancel()
}

func (c *Client) Session(opts ...SessionOption) (session *Session, err error) {
	req := &browserservicev1.SessionRequest{}
	for _, opt := range opts {
		opt(req)
	}

	ctx, cancel := context.WithCancel(context.Background())
	defer func() {
		if err != nil {
			cancel()
		}
	}()

	stream, err := c.svc.Session(ctx, req)
	if err != nil {
		return nil, fmt.Errorf("could not open session stream: %w", err)
	}

	resp, err := stream.Recv()
	if err != nil {
		return nil, fmt.Errorf("could not receive session response: %w", err)
	}

	return &Session{
		controlURL: resp.GetControlUrl(),
		cancel:     cancel,
	}, nil
}
