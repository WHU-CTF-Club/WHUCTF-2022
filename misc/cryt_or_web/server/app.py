from flask import Flask
from flask import render_template, redirect, url_for
from flask import request, session

app = Flask(__name__)


@app.before_request
def before_action():
    print (request.path)
    if request.path.find('.png') == -1:
        if not request.path == '/kawaiiiMia':
            if not 'key' in session:
                return redirect(url_for('kawaiiiMia'))


@app.route('/kawaiiiMia', methods=['GET','POST'])
def kawaiiimia():
    error = 'Not Post'
    if request.method == 'POST':
        if request.form['key'] == 'maybemaybe':
            session['key'] = request.form['key']
            return redirect('/maybeflag')
        else:
            error = 'Invalid key'
    return render_template('kawaiiiMia.html', error= error)


@app.route('/maybeflag')
def maybeflag():
    return render_template('maybeflag.txt', key=session['key'])


app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'

if __name__ == '__main__':
    app.debug = True
    app.run('0.0.0.0', 80)