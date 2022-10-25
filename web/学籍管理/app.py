from flask import Flask,session,render_template_string,render_template,redirect,request,url_for
import re
app = Flask(__name__)
app.config["SECRET_KEY"] = 'may_ctf'


@app.route("/",methods=['GET','POST'])
@app.route("/login",methods=['GET','POST'])
def login():
   session['name'] = ''
   if request.method == 'POST':
      name = request.form.get('name')
      id = request.form.get('id')
      if not ((len(id) == 13) and (id[0:4] == '2022' or id[0:4] == '2021' or id[0:4] == '2020')):
         js = '''
                     <script> alert('该学号不存在！'); 
                     window.history.back(-1); 
                     </script>
                     '''
         return render_template_string(js)
      elif re.search(r"\W",name):
         js = '''
                              <script> alert('该姓名不存在！'); 
                              window.history.back(-1); 
                              </script>
                              '''
         return render_template_string(js)
      else:
         session['name'] = name
         session['usr'] = 'student'
         session['what do you want to do'] = 'Ohhhhhhh you are hacker!'
         return redirect(url_for('index'))
   else:
      return render_template('login.html')


@app.route("/index",methods=['GET','POST'])
def index():
   if session.get('name') != '':
      name = session.get('name')
      if request.method == 'POST':
         message = request.form.get('message')
         if  'flag' in message  or 'templates' in message or 'static' in message:
            js = '''
                     <script> alert('You are hacker！'); 
                     window.history.back(-1); 
                     </script>
                     '''
            return render_template_string(js)
         else:
            html = '''
         <!DOCTYPE html>
         <html lang="en">
          <head>
              <meta charset="UTF-8">
              <title>index</title>
              <link rel="stylesheet" href="static/index.css">
          </head>
          <body>
              <div class="top">
              </div>
              <div class="title">
                  武氵又大学
              </div>
              <h2>
                  <span>你好，%s同学,你被武氵又大学退学了</span>
              </h2>
               <div class='image1'>
              <img src="static/index1.jpg"   width=400px, height=300px>
              </div>
              <div class='image2'>
              <img src="static/index2.jpg" width=400px, height=300px>
              </div>
              <div class="divform" >
                 <form action="index" method="POST" >
                    <h3>
                      <span>你有什么想对校长说的话可以写在这里</span>
                    </h3>
                    <div class="item">
                      <input type="text" placeholder="这会发到校长邮箱" name='message'>
                    </div>
                    <div class="button" >
                      <button>提交</button>
                    </div>
                 </form>
              </div>
      
               <p>感谢您的意见，"%s"已提交！</p>
      
      
         <form action="/regulation" method="GET">
          <div class="manage"  >
          <button >学籍管理</button>
        </div>
        </form>
           </body>
         </html>  ''' %(name,message)
            return render_template_string(html)
      else:
         return render_template('index.html',name=name)

   else:
      js = '''
            <script> alert('请先登录！'); 
            window.history.back(-1); 
            </script>
            '''
      return render_template_string(js)

@app.route("/regulation",methods=['GET','POST'])
def regulation():
   if session.get('name') != '':
      usr = session.get('usr')
      if usr == 'admin':
         return render_template('flag.html')
      else:
         js = '''
         <script> alert('You are not admin！'); 
         window.history.back(-1); 
         </script>
         '''
      return render_template_string(js)
   else:
      js = '''
                  <script> alert('请先登录！'); 
                  window.history.back(-1); 
                  </script>
                  '''
      return render_template_string(js)


if __name__=="__main__":
       app.run(host='0.0.0.0', port=80)