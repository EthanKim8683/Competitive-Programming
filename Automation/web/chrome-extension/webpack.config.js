const glob = require("glob");
const path = require("path");
const CopyWebpackPlugin = require("copy-webpack-plugin");
const DotenvWebpackPlugin = require("dotenv-webpack");

const src = path.join(__dirname, "src");

module.exports = {
  entry: Object.fromEntries(
    glob
      .sync("**/*.ts", {
        cwd: src,
        ignore: ["node_modules", "**/*.d.ts"],
      })
      .map((file) => {
        const { dir, name } = path.parse(file);
        return [path.join(dir, name), path.join(src, file)];
      })
  ),
  devtool: "source-map",
  output: {
    path: path.resolve(__dirname, "build"),
    filename: "[name].js",
    clean: true,
  },
  resolve: {
    extensions: [".ts", ".js"],
  },
  module: {
    rules: [
      {
        test: /\.ts$/,
        use: "ts-loader",
      },
    ],
  },
  plugins: [
    new CopyWebpackPlugin({
      patterns: [
        {
          from: "**/*",
          context: "public",
        },
      ],
    }),
    new DotenvWebpackPlugin({
      path: ".env",
    }),
  ],
};
