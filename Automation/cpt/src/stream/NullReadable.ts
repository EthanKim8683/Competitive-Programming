import { Readable, ReadableOptions } from "stream";

export default class extends Readable {
	constructor(options?: ReadableOptions) {
		super(options);
	}

	_read(): void {}
}
