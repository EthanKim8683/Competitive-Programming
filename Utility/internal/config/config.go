package config

import (
	"fmt"

	"github.com/caarlos0/env/v11"
	"go.uber.org/multierr"
)

type BrowserConfig struct {
	GRPCPort int `env:"BROWSER_GRPC_PORT"`

	Bin                 string `env:"CHROME_EXECUTABLE_PATH"`
	RemoteDebuggingPort int    `env:"CHROME_REMOTE_DEBUGGING_PORT"`
	UserDataDir         string `env:"CHROME_USER_DATA_DIR"`
	ProfileDir          string `env:"CHROME_PROFILE_DIRECTORY"`
}

func (c *BrowserConfig) Validate() (err error) {
	if c.GRPCPort == c.RemoteDebuggingPort && c.GRPCPort != 0 {
		err = multierr.Append(err, fmt.Errorf("GRPCPort and RemoteDebuggingPort must be different"))
	}

	return err
}

type Config struct {
	Browser BrowserConfig
}

func (c *Config) Validate() (err error) {
	err = multierr.Append(err, c.Browser.Validate())
	return err
}

func Load() (Config, error) {
	var cfg Config
	if err := env.Parse(&cfg); err != nil {
		return Config{}, fmt.Errorf("failed to parse config: %w", err)
	}
	if err := cfg.Validate(); err != nil {
		return Config{}, fmt.Errorf("invalid config: %w", err)
	}
	return cfg, nil
}
