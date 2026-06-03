package config

type BrowserConfig struct {
	GRPCPort int `env:"BROWSER_GRPC_PORT"`

	Bin                 string `env:"CHROME_EXECUTABLE_PATH"`
	RemoteDebuggingPort int    `env:"CHROME_REMOTE_DEBUGGING_PORT"`
	UserDataDir         string `env:"CHROME_USER_DATA_DIR"`
	ProfileDir          string `env:"CHROME_PROFILE_DIRECTORY"`
}

type Config struct {
	BrowserConfig BrowserConfig
}

func Load() (Config, error) {
	// TODO: load from env; ensure GRPCPort != RemoteDebuggingPort
	return Config{}, nil
}
