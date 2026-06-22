local filename = debug.getinfo(1, "S").source:sub(2)
local dirname = vim.fn.fnamemodify(filename, ":p:h")

require("luasnip.loaders.from_lua").load({
	paths = { dirname .. "/Snippets/LuaSnip" },
})
