import { ChildProcess } from "child_process";

export default (
	children: ChildProcess[]
): Promise<
	| {
			success: false;
			index: number;
			code: number | null;
			signal: NodeJS.Signals | null;
	  }
	| { success: true }
> => {
	return new Promise((resolve, reject) => {
		function killAll() {
			const kills = children.map((child) =>
				// child.exitCode is null if the child is still running
				child.exitCode ? false : child.kill()
			);
			if (kills.includes(true)) reject("Could not kill some children");
		}

		let fulfilled = 0;
		children.forEach((child, index) =>
			child.on("close", (code, signal) => {
				if (code !== 0 || signal) {
					killAll();
					resolve({
						success: false,
						index,
						code,
						signal,
					});
				}

				fulfilled++;
				if (fulfilled === children.length) {
					resolve({
						success: true,
					});
				}
			})
		);
	});
};
