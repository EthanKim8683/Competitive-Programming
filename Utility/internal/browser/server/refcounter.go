package server

import "sync"

type refCounter struct {
	mu sync.Mutex

	count int

	browser *browser
}

func (rc *refCounter) acquire() (func(), error) {
	rc.mu.Lock()
	defer rc.mu.Unlock()

	if rc.count == 0 {
		if err := rc.browser.launch(); err != nil {
			return nil, err
		}
	}
	rc.count++

	var once sync.Once
	return func() {
		once.Do(func() {
			rc.mu.Lock()
			defer rc.mu.Unlock()

			rc.count--
			if rc.count == 0 {
				rc.browser.kill()
			}
		})
	}, nil
}

func newRefCounter(browser *browser) *refCounter {
	return &refCounter{
		browser: browser,
	}
}
