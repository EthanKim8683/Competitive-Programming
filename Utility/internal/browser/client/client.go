package client

import (
	"context"
	"fmt"
	"time"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/config"
	browserservicev1 "github.com/EthanKim8683/Competitive-Programming/Utility/internal/gen/browserservice/v1"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

type Client struct {
	conn *grpc.ClientConn
	svc  browserservicev1.BrowserServiceClient
}

func Dial(ctx context.Context, cfg config.BrowserConfig, opts ...grpc.DialOption) (*Client, error) {
	if err := ensureDaemon(ctx, cfg); err != nil {
		return nil, err
	}

	opts = append([]grpc.DialOption{grpc.WithTransportCredentials(insecure.NewCredentials())}, opts...)
	conn, err := grpc.NewClient(fmt.Sprintf("127.0.0.1:%d", cfg.GRPCPort), opts...)
	if err != nil {
		return nil, err
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

func (c *Client) Session(ctx context.Context, opts ...SessionOption) (controlURL string, err error) {
	req := &browserservicev1.SessionRequest{}
	for _, opt := range opts {
		opt(req)
	}

	ctx, cancel := context.WithCancel(ctx)
	defer func() {
		if err != nil {
			cancel()
		}
	}()

	stream, err := c.svc.Session(ctx, req)
	if err != nil {
		return "", err
	}

	resp, err := stream.Recv()
	if err != nil {
		return "", err
	}

	return resp.GetControlUrl(), nil
}
