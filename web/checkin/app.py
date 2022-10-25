from flask import Flask, render_template, request, render_template_string
import hashlib
app = Flask(__name__)

@app.route('/',methods=['GET','POST'])
@app.route('/checkin',methods=['GET','POST'])
def login():
    if request.method == 'GET':
        return render_template('index.html')
    else:
        id = request.form.get('id')
        value = request.form.get('value')
        key = '972513'
        if not (id.isdigit() and(len(id) == 13) and (id[0:4] == '2022' or id[0:4] == '2021' or id[0:4] == '2020')):
            js = ''' <script> alert('该学号不存在！'); 
                    window.history.back(-1); 
                    </script>
                    '''
            return render_template_string(js)
        elif id == 2021302181171 or id == 2022111111111:
            js = ''' <script> alert('该同学签到过了！！'); 
                    window.history.back(-1); 
                    </script>
                    '''
            return render_template_string(js)
        else:
            number = id + key
            number = int(number)
            m = hashlib.md5()
            m.update(b'%d'%(number))
            if m.hexdigest() == value.lower():
                js = '''<script> alert('签到成功！');
                        alert('上课千万不要迟到哦！');
                        alert('flag{y0u_ha7e_che3ke8_in_suc5c3ssfu7ly}')
                        window.history.back(-1); 
                        </script>
                     '''
            else:
                js = ''' <script> alert('签到失败！'); 
                                    window.history.back(-1); 
                                    </script>
                                    '''
            return render_template_string(js)

if  __name__ == "__main__":
    app.run(debug=False,host='0.0.0.0',port=80)