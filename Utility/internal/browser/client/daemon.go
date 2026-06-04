package client

import (
	"context"
	"fmt"
	"io"
	"net"
	"os/exec"
	"syscall"
	"time"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/config"
)

const pollInterval = 100 * time.Millisecond

func tryTCPDial(ctx context.Context, cfg config.BrowserConfig) error {
	var d net.Dialer
	conn, err := d.DialContext(ctx, "tcp", fmt.Sprintf("127.0.0.1:%d", cfg.GRPCPort))
	if err != nil {
		return err
	}
	return conn.Close()
}

func startDaemon(ctx context.Context, cfg config.BrowserConfig) error {
	cmd := exec.CommandContext(ctx, cfg.DaemonCommand)
	cmd.Stdout = io.Discard
	cmd.Stderr = io.Discard
	cmd.SysProcAttr = &syscall.SysProcAttr{
		Setpgid: true,
	}

	if err := cmd.Start(); err != nil {
		return err
	}

	return nil
}

func waitForTCPConn(ctx context.Context, cfg config.BrowserConfig) error {
	ticker := time.NewTicker(pollInterval)
	defer ticker.Stop()

	for {
		if err := tryTCPDial(ctx, cfg); err == nil {
			return nil
		}

		select {
		case <-ctx.Done():
			return fmt.Errorf("browser daemon not ready: %w", ctx.Err())
		case <-ticker.C:
		}
	}
}

func ensureDaemon(ctx context.Context, cfg config.BrowserConfig) error {
	if err := tryTCPDial(ctx, cfg); err == nil {
		return nil
	}
	if err := startDaemon(ctx, cfg); err != nil {
		return err
	}
	if err := waitForTCPConn(ctx, cfg); err != nil {
		return err
	}
	return nil
}
