import templates as templates
from flask import Flask, render_template, jsonify, request, redirect, url_for

app = Flask(__name__)

DATA_DICT = {
    1: {'name': '西奥', 'age': 73},
    2: {'name': '旺财', 'age': 84}
}

@app.route('/', methods={'GET', 'POST'})
def get_RSA():
    if request.method == 'GET':
        return render_template('error.html')  # HttpResponse
    print(request.form)
    user = request.form.get('user')
    pwd = request.form.get('pwd')
    if user == '123' and pwd == '456':
        return redirect('/index')
    else:
        error = '用户名或密码错误'
        return render_template('about.html', error=error)


@app.route('/index', endpoint='idx')
def index():
    data_dict = DATA_DICT
    return render_template('index.html', data_dict=data_dict)

# 4.falsk使用动态路由
# 5. request.args 为GET形式传递的参数
# 6. request.form 为POST形式提交的参数
# @app.route('/edit/<int:nid>')
@app.route('/edit', methods={'GET', 'POST'})
def edit():
    nid = request.args.get('nid')
    nid = int(nid)
    if request.method == 'GET':
        info = DATA_DICT[nid]
        return render_template('edit.html', info=info)

    user = request.form.get('user')
    age = request.form.get('age')
    DATA_DICT[nid]['name'] = user
    DATA_DICT[nid]['age'] = age

    return redirect(url_for('idx'))
    
# 返回数据形式
# 1. return render_template('模板文件')
# 2. return jasonify
# 3. return redirect('/index')(传url) 
#或者 redirect(url_for('别名'))
# 4. return "字符串"

# 模板处理 for 循环
# 1. {% for key, value in data_dict.items() %}
#		{{iterm}}
#	 {% endfor %}
@app.route('/del/<int:nid>')
def delete(nid):
    del DATA_DICT[nid]
    # return redirect('/index')
    return redirect(url_for("idx"))


if __name__ == '__main__':
    app.run()

