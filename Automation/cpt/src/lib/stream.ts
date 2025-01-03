import { Writable, WritableOptions } from "stream";

export class WritableString extends Writable {
	private _string: string = "";

	constructor(options?: WritableOptions) {
		super(options);
	}

	get string() {
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
