from flask import Flask, render_template, request
import subprocess

app = Flask(__name__)


@app.route("/", methods=["GET", "POST"])
def index():
    result = None
    if request.method == "POST":
        # 获取表单输入
        output_format = request.form.get("output_format")
        operator = request.form.get("operator")
        poly1 = request.form.get("poly1")
        poly2 = request.form.get("poly2")
        # print(output_format, operator, poly1, poly2)

        # 判断是否需要poly2（比如求导操作只需要poly1）
        if operator in ["+", "-", "*"]:  # 假设这些操作符需要poly2
            input_data = f"{output_format}\n{operator}\n{poly1}\n{poly2}\n"
        else:  # 其他操作符，比如求导，只需要poly1
            input_data = f"{output_format}\n{operator}\n{poly1}\n"
        print(input_data)
        try:
            # 使用 Popen 调用 C 程序并通过标准输入传递参数
            process = subprocess.Popen(
                ["cmake-build-release/CPolynomialCalculator.exe"],  # C 程序的路径
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
            )
            # 传递标准输入
            stdout, stderr = process.communicate(input=input_data)
            print(stdout, stderr)

            if stderr:
                result = f"Error: {stderr}"
            else:
                result = stdout
        except Exception as e:
            result = f"Exception occurred: {str(e)}"

    return render_template("index.html", result=result)


if __name__ == "__main__":
    app.run(debug=True)
