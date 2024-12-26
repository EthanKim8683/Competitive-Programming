import { Writable, WritableOptions } from "stream";

export default class extends Writable {
	constructor(options?: WritableOptions) {
		super(options);
	}

	_write() {}
}
