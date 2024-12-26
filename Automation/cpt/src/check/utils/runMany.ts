import run from "../../run/run";

export default (
	runs: ReturnType<typeof run>[]
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
			const kills = runs.map(({ child }) =>
				// child.exitCode is null if the child is still running
				child.exitCode ? false : child.kill()
			);
			if (kills.includes(true)) reject("Could not kill some processes");
		}

		let fulfilled = 0;
		runs.forEach(({ exit }, index) =>
			exit.then(({ code, signal }) => {
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
				if (fulfilled === runs.length) {
					resolve({
						success: true,
					});
				}
			})
		);
	});
};
