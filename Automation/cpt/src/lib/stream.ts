import { Writable, WritableOptions } from "stream";

export class WritableString extends Writable {
	#string: string = "";

	constructor(options?: WritableOptions) {
		super(options);
	}

	get string() {
		return this.#string;
	}

	_write(
		chunk: Buffer | string | any,
		encoding: BufferEncoding | "buffer",
		callback: (error?: Error | null) => void
	): void {
		this.#string += chunk.toString(
			encoding === "buffer" ? undefined : encoding
		);
		callback();
	}
}
