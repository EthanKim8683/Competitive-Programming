package automation

import (
	"github.com/nats-io/nats.go"
	"google.golang.org/protobuf/proto"
)

func rpc(subject string, request proto.Message, response proto.Message) error {
	nc, err := nats.Connect("nats://127.0.0.1:4222")
	if err != nil {
		return err
	}
	defer nc.Close()

	data, err := proto.Marshal(request)
	if err != nil {
		return err
	}

	msg, err := nc.Request(subject, data, nats.DefaultTimeout)
	if err != nil {
		return err
	}

	if err := proto.Unmarshal(msg.Data, response); err != nil {
		return err
	}

	return nil
}
