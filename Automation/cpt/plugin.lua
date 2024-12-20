local function CptSetup()
	input = vim.api.nvim_open_win(0, false, {
		split = "right",
		width = 50,
		style = "minimal",
	})
	output = vim.api.nvim_open_win(0, false, {
		win = input,
		split = "below",
		style = "minimal",
	})
	term_win = vim.api.nvim_open_win(0, false, {
		split = "below",
		height = 10,
		style = "minimal"
	})
end

local function setup()
	vim.api.nvim_create_user_command("CptSetup", CptSetup, {
		bang = true
	})
end

return { setup = setup }
