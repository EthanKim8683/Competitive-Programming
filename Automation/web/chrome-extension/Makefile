include ../../../Makefile.Common

.env: .env.template
	envsubst < .env.template > .env

build: .env
	npm run build