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

func Dial(ctx context.Context, cfg config.BrowserConfig, opts ...grpc.DialOption) (client *Client, err error) {
	opts = append([]grpc.DialOption{
		grpc.WithTransportCredentials(insecure.NewCredentials()),
	}, opts...)
	conn, err := grpc.NewClient(fmt.Sprintf("127.0.0.1:%d", cfg.GRPCPort), opts...)
	if err != nil {
		return nil, err
	}

	conn.Connect()
	defer func() {
		if err != nil {
			conn.Close()
		}
	}()

	for state := conn.GetState(); state != connectivity.Ready; state = conn.GetState() {
		if state == connectivity.Shutdown {
			return nil, errors.New("connection shut down")
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

type acquireConfig struct {
	ctx context.Context
	req *browserservicev1.SessionRequest
}

type AcquireOption func(*acquireConfig)

func WithContext(ctx context.Context) AcquireOption {
	return func(cfg *acquireConfig) {
		cfg.ctx = ctx
	}
}

func WithKeepAlive(timeout time.Duration) AcquireOption {
	return func(cfg *acquireConfig) {
		cfg.req.KeepAlive = &browserservicev1.SessionRequest_KeepAlive{
			TimeoutMs: uint32(timeout.Milliseconds()),
		}
	}
}

type Handle struct {
	controlURL string
	cancel     context.CancelFunc
}

func (h *Handle) ControlURL() string {
	return h.controlURL
}

func (h *Handle) Release() {
	h.cancel()
}

func (c *Client) Acquire(opts ...AcquireOption) (handle *Handle, err error) {
	cfg := &acquireConfig{
		ctx: context.Background(),
		req: &browserservicev1.SessionRequest{},
	}
	for _, opt := range opts {
		opt(cfg)
	}

	ctx, cancel := context.WithCancel(cfg.ctx)
	defer func() {
		if err != nil {
			cancel()
		}
	}()

	stream, err := c.svc.Session(ctx, cfg.req)
	if err != nil {
		return nil, fmt.Errorf("could not open session stream: %w", err)
	}

	resp, err := stream.Recv()
	if err != nil {
		return nil, fmt.Errorf("could not receive session response: %w", err)
	}

	return &Handle{
		controlURL: resp.GetControlUrl(),
		cancel:     cancel,
	}, nil
}
