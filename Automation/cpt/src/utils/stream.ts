import { Readable, ReadableOptions, Writable, WritableOptions } from "stream";

export class NullReadable extends Readable {
	constructor(options?: ReadableOptions) {
		super(options);
	}

	_read(): void {}
}

export class NullWritable extends Writable {
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

export class WritableString extends Writable {
	private _string: string = "";

	constructor(options?: WritableOptions) {
		super(options);
	}

	get string(): string {
		return this._string;
	}

	_write(
		chunk: Buffer | string | any,
		encoding: BufferEncoding | "buffer",
		callback: (error?: Error | null) => void
	): void {
		this._string += chunk.toString(
			encoding === "buffer" ? undefined : encoding
		);
		callback();
	}
}
