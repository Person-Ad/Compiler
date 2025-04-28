from flask import Flask, request, Response
import subprocess
import os

app = Flask(__name__)

@app.route('/run', methods=['POST'])
def run_code():
    code = request.data.decode('utf-8')
    if not code:
        return Response("Missing code in request body\n", status=400, mimetype='text/plain')

    try:
        # 1. Write code to tmp_code.txt
        with open('tmp_code.txt', 'w', encoding='utf-8') as tmpfile:
            tmpfile.write(code)

        # 2. Run base.exe like your .bat: read tmp_code.txt
        ret = subprocess.run(
            ['cmd', '/c', 'base.exe < tmp_code.txt'],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            shell=True
        )

        if ret.returncode != 0:
            return Response(
                f"base.exe execution failed\nSTDOUT:\n{ret.stdout.decode()}\nSTDERR:\n{ret.stderr.decode()}\n",
                status=500,
                mimetype='text/plain'
            )

        # 3. Collect outputs
        result = []
        if os.path.exists('quadruples.txt'):
            with open('quadruples.txt', 'r', encoding='utf-8') as f:
                result.append('=== Quadruples ===\n' + f.read())

        if os.path.exists('tracked_tables.txt'):
            with open('tracked_tables.txt', 'r', encoding='utf-8') as f:
                result.append('=== Tracked Tables ===\n' + f.read())

        if os.path.exists('errors_and_warnings.txt'):
            with open('errors_and_warnings.txt', 'r', encoding='utf-8') as f:
                result.append('=== Errors and Warnings ===\n' + f.read())

        return Response('\n\n'.join(result), mimetype='text/plain')

    except Exception as e:
        return Response(f"Server error: {str(e)}", status=500, mimetype='text/plain')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
