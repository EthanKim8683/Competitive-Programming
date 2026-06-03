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

func Dial(cfg config.BrowserConfig, opts ...grpc.DialOption) (*Client, error) {
	opts = append([]grpc.DialOption{
		grpc.WithTransportCredentials(insecure.NewCredentials()),
	}, opts...)

	conn, err := grpc.NewClient(
		fmt.Sprintf("127.0.0.1:%d", cfg.GRPCPort),
		opts...,
	)
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
	return c.conn.Close()
}

func (c *Client) Acquire(ttl time.Duration) error {
	_, err := c.svc.Acquire(context.Background(), &browserservicev1.AcquireRequest{
		TtlMs: uint32(ttl.Milliseconds()),
	})
	return err
}

func (c *Client) ControlURL() (string, error) {
	resp, err := c.svc.ControlURL(context.Background(), &browserservicev1.ControlURLRequest{})
	if err != nil {
		return "", err
	}
	return resp.GetControlUrl(), nil
}
