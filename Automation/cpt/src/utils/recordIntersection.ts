export default <T extends string | number | symbol, S>(
	record1: Record<T, S>,
	record2: Record<T, S>
): [Record<T, S>, Record<T, S>] => {
	const intersectedRecord1 = {} as Record<T, S>,
		intersectedRecord2 = {} as Record<T, S>;
	for (const key in record1)
		if (key in record2) {
			intersectedRecord1[key] = record1[key];
			intersectedRecord2[key] = record2[key];
		}
	return [intersectedRecord1, intersectedRecord2];
};
