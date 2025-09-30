const fs = require("fs");
const path = require("path");
const CopyWebpackPlugin = require("copy-webpack-plugin");

const src = path.join(__dirname, "src");

module.exports = {
  entry: Object.fromEntries(
    fs
      .globSync("**/*.ts", {
        cwd: src,
        exclude: ["node_modules"],
      })
      .map((file) => {
        const { name } = path.parse(file);
        return [name, path.join(src, file)];
      })
  ),
  devtool: "source-map",
  output: {
    path: path.resolve(__dirname, "build"),
    filename: "[name].js",
    clean: true,
  },
  resolve: {
    extensions: [".ts"],
  },
  module: {
    rules: [
      {
        test: /\.ts$/,
        use: "ts-loader",
        exclude: /^node_modules$/,
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
  ],
};
