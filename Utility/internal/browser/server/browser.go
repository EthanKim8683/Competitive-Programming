package server

import (
	"context"
	"database/sql"
	"errors"
	"fmt"
	"io"
	"net/url"
	"os"
	"path/filepath"
	"sync"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/config"
	"github.com/go-rod/rod/lib/launcher"
	_ "modernc.org/sqlite"
)

const (
	userDataDirPattern = "user-data-dir-*"
	profileDir         = "Default"
	busyTimeoutMS      = 5000
)

type browser struct {
	cfg config.BrowserConfig

	mu          sync.RWMutex
	userDataDir string
	launcher    *launcher.Launcher
	wsURL       string
}

func copyLocalState(src string, dst string) error {
	in, err := os.Open(src)
	if err != nil {
		if os.IsNotExist(err) {
			return fmt.Errorf("local state file not found: %w", err)
		}
		return fmt.Errorf("failed to open local state file: %w", err)
	}
	defer in.Close()

	out, err := os.Create(dst)
	if err != nil {
		return fmt.Errorf("failed to create local state file: %w", err)
	}
	defer out.Close()

	_, err = io.Copy(out, in)
	if err != nil {
		return fmt.Errorf("failed to copy local state: %w", err)
	}
	return nil
}

func cookiesDSN(src string) string {
	u := url.URL{
		Scheme: "file",
		Path:   filepath.ToSlash(src),
	}
	q := u.Query()
	q.Add("_pragma", fmt.Sprintf("busy_timeout(%d)", busyTimeoutMS))
	q.Set("mode", "ro")
	u.RawQuery = q.Encode()
	return u.String()
}

func copyCookies(ctx context.Context, src string, dst string) error {
	if _, err := os.Stat(src); err != nil {
		if os.IsNotExist(err) {
			return nil
		}
		return fmt.Errorf("failed to stat cookies file: %w", err)
	}

	db, err := sql.Open("sqlite", cookiesDSN(src))
	if err != nil {
		return fmt.Errorf("failed to open cookies file: %w", err)
	}
	defer db.Close()

	_, err = db.ExecContext(ctx, "VACUUM INTO ?", dst)
	if err != nil {
		return fmt.Errorf("failed to vacuum cookies file: %w", err)
	}

	return nil
}

func (b *browser) launch(ctx context.Context) (err error) {
	b.mu.Lock()
	defer b.mu.Unlock()

	if b.launcher != nil {
		return nil
	}

	userDataDir, err := os.MkdirTemp(os.TempDir(), userDataDirPattern)
	if err != nil {
		return fmt.Errorf("failed to create user data directory: %w", err)
	}
	defer func() {
		if err != nil {
			os.RemoveAll(userDataDir)
		}
	}()

	if err := os.Mkdir(filepath.Join(userDataDir, profileDir), 0o755); err != nil {
		return fmt.Errorf("failed to create profile directory: %w", err)
	}

	if err := copyLocalState(
		filepath.Join(b.cfg.UserDataDir, "Local State"),
		filepath.Join(userDataDir, "Local State"),
	); err != nil {
		return fmt.Errorf("failed to copy local state: %w", err)
	}

	if err := copyCookies(
		ctx,
		filepath.Join(b.cfg.UserDataDir, b.cfg.ProfileDir, "Cookies"),
		filepath.Join(userDataDir, profileDir, "Cookies"),
	); err != nil {
		return fmt.Errorf("failed to copy cookies: %w", err)
	}

	l := launcher.New().
		Context(ctx).
		Bin(b.cfg.Bin).
		RemoteDebuggingPort(b.cfg.RemoteDebuggingPort).
		UserDataDir(userDataDir).
		ProfileDir(profileDir).
		Leakless(true).
		Headless(true).
		Delete("use-mock-keychain").
		Delete("enable-automation").
		Set("password-store", "keychain")

	wsURL, err := l.Launch()
	if err != nil {
		return fmt.Errorf("failed to launch browser: %w", err)
	}

	b.userDataDir = userDataDir
	b.launcher = l
	b.wsURL = wsURL

	return nil
}

func (b *browser) controlURL() (string, error) {
	b.mu.RLock()
	defer b.mu.RUnlock()

	if b.launcher == nil {
		return "", errors.New("browser not running")
	}

	return b.wsURL, nil
}

func (b *browser) kill() {
	b.mu.Lock()
	defer b.mu.Unlock()

	if b.launcher == nil {
		return
	}

	b.launcher.Kill()
	_ = os.RemoveAll(b.userDataDir)

	b.wsURL = ""
	b.launcher = nil
	b.userDataDir = ""
}

func newBrowser(cfg config.BrowserConfig) *browser {
	return &browser{
		cfg: cfg,
	}
}
