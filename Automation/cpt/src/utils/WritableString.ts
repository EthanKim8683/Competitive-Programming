import { Writable, WritableOptions } from "stream";

export default class extends Writable {
	#string: string = "";

	constructor(options?: WritableOptions) {
		super(options);
	}

	get string() {
		return this.#string;
	}

	_write(data: string) {
		this.#string += data;
	}
}
