import { Writable, WritableOptions } from "stream";

export default class extends Writable {
	constructor(options?: WritableOptions) {
		super(options);
	}

	_write(
		_chunk: Buffer | string | any,
		_encoding: BufferEncoding | "buffer",
		callback: (error?: Error | null) => void
	): void {
		callback();
	}
}
