import * as chai from "chai";
import chaiAsPromised from "chai-as-promised";
import os from "os";
import path from "path";
import fs from "fs/promises";
import cp from "child_process";
import { promisify } from "util";
const exec = promisify(cp.exec);
import z from "zod";
import compile from "../runner-utils/compile.mjs";
import execute from "../runner-utils/execute.mjs";

chai.use(chaiAsPromised);
chai.should();
chai.config.truncateThreshold = 0;

let tmpdir;
before(() => {
  tmpdir = os.tmpdir();
});

describe("runner-utils", () => {
  describe("compile", () => {
    before(async () => {
      await fs.writeFile(path.join(tmpdir, "error.cpp"), "");
      await fs.writeFile(
        path.join(tmpdir, "warning.cpp"),
        "int main(){char x=256;}"
      );
      await fs.writeFile(path.join(tmpdir, "ok.cpp"), "int main(){}");
    });

    it("should return { error: <string>, warning: undefined } when compilation has error(s)", () => {
      const schema = z.object({
        error: z.string(),
        warning: z.undefined(),
      });

      return compile([
        "/opt/homebrew/bin/g++-14",
        "-o",
        path.join(tmpdir, "o"),
        path.join(tmpdir, "error.cpp"),
      ]).then((rv) => schema.parse(rv)).should.be.fulfilled;
    });

    it("should return { error: undefined, warning: <string> } when compilation has warning(s)", () => {
      const schema = z.object({
        error: z.undefined(),
        warning: z.string(),
      });

      return compile([
        "/opt/homebrew/bin/g++-14",
        "-o",
        path.join(tmpdir, "o"),
        path.join(tmpdir, "warning.cpp"),
      ]).then((rv) => schema.parse(rv)).should.be.fulfilled;
    });

    it("should return { error: undefined, warning: undefined } when compilation is ok", () => {
      const schema = z.object({
        error: z.undefined(),
        warning: z.undefined(),
      });

      return compile([
        "/opt/homebrew/bin/g++-14",
        "-o",
        path.join(tmpdir, "o"),
        path.join(tmpdir, "ok.cpp"),
      ]).then((rv) => schema.parse(rv)).should.be.fulfilled;
    });

    it("should return { error: undefined, warning: undefined } when nothing to compile", () => {
      const schema = z.object({
        error: z.undefined(),
        warning: z.undefined(),
      });

      return compile([]).then((rv) => schema.parse(rv)).should.be.fulfilled;
    });
  });

  describe("execute", () => {
    before(async () => {
      await exec(
        [
          "echo",
          '"int main(){*(int*)0=0;}"',
          "|",
          "/opt/homebrew/bin/g++-14",
          "-x",
          "c++",
          "-o",
          path.join(tmpdir, "error"),
          "-",
        ].join(" ")
      );
      await exec(
        [
          "echo",
          '"int main(){}"',
          "|",
          "/opt/homebrew/bin/g++-14",
          "-x",
          "c++",
          "-o",
          path.join(tmpdir, "ok"),
          "-",
        ].join(" ")
      );
    });

    it("should return { code: null, signal: <string>, maxrss: <nonneg int>, cpu: <nonneg float> } when execution is terminated", () => {
      const schema = z.object({
        code: z.null(),
        signal: z.string(),
        maxrss: z.number().nonnegative().int(),
        cpu: z.number().nonnegative(),
      });

      return execute([
        path.relative(process.cwd(), path.join(tmpdir, "error")),
      ]).then((rv) => schema.parse(rv)).should.be.fulfilled;
    });

    it("should return { code: <int>, signal: null, maxrss: <nonneg int>, cpu: <nonneg float> } when execution exits gracefully", () => {
      const schema = z.object({
        code: z.number().int(),
        signal: z.null(),
        maxrss: z.number().nonnegative().int(),
        cpu: z.number().nonnegative(),
      });

      return execute([
        path.relative(process.cwd(), path.join(tmpdir, "ok")),
      ]).then((rv) => schema.parse(rv)).should.be.fulfilled;
    });
  });
});
