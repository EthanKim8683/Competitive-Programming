package server

import (
	"errors"
	"fmt"
	"io"
	"os"
	"os/exec"
	"path/filepath"
	"sync"

	"github.com/EthanKim8683/Competitive-Programming/Utility/internal/config"
	"github.com/go-rod/rod/lib/launcher"
)

func copyFile(src string, dst string) error {
	in, err := os.Open(src)
	if err != nil {
		return err
	}
	defer in.Close()

	if err := os.MkdirAll(filepath.Dir(dst), 0o755); err != nil {
		return err
	}

	out, err := os.Create(dst)
	if err != nil {
		return err
	}
	defer out.Close()

	_, err = io.Copy(out, in)
	return err
}

func copySQLiteFile(src string, dst string) error {
	return exec.Command("sqlite3", src, fmt.Sprintf(`.backup '%s'`, dst)).Run()
}

type browser struct {
	cfg config.BrowserConfig

	mu sync.RWMutex

	userDataDir string
	launcher    *launcher.Launcher
	wsURL       string
	isLaunched  bool
}

func (b *browser) launch() error {
	b.mu.Lock()
	defer b.mu.Unlock()

	if b.isLaunched {
		return nil
	}

	userDataDir, err := os.MkdirTemp(os.TempDir(), "*")
	if err != nil {
		return err
	}
	defer func() {
		if !b.isLaunched {
			os.RemoveAll(userDataDir)
		}
	}()

	if err := os.MkdirAll(filepath.Join(userDataDir, b.cfg.ProfileDir), 0o755); err != nil {
		return err
	}

	if err := copyFile(
		filepath.Join(b.cfg.UserDataDir, "Local State"),
		filepath.Join(userDataDir, "Local State"),
	); err != nil {
		return err
	}

	if err := copySQLiteFile(
		filepath.Join(b.cfg.UserDataDir, b.cfg.ProfileDir, "Cookies"),
		filepath.Join(userDataDir, b.cfg.ProfileDir, "Cookies"),
	); err != nil {
		return err
	}

	ln := launcher.New().
		Bin(b.cfg.Bin).
		RemoteDebuggingPort(b.cfg.RemoteDebuggingPort).
		UserDataDir(userDataDir).
		ProfileDir(b.cfg.ProfileDir).
		Leakless(true).
		Headless(true).
		Delete("use-mock-keychain").
		Delete("enable-automation").
		Set("password-store", "keychain")

	wsURL, err := ln.Launch()
	if err != nil {
		return err
	}

	b.userDataDir = userDataDir
	b.launcher = ln
	b.wsURL = wsURL
	b.isLaunched = true

	return nil
}

func (b *browser) controlURL() (string, error) {
	b.mu.RLock()
	defer b.mu.RUnlock()

	if !b.isLaunched {
		return "", errors.New("browser not running")
	}

	return b.wsURL, nil
}

func (b *browser) kill() {
	b.mu.Lock()
	defer b.mu.Unlock()

	if !b.isLaunched {
		return
	}

	b.launcher.Kill()

	os.RemoveAll(b.userDataDir)

	b.userDataDir = ""
	b.launcher = nil
	b.wsURL = ""
	b.isLaunched = false
}

func newBrowser(cfg config.BrowserConfig) *browser {
	return &browser{
		cfg: cfg,
	}
}
