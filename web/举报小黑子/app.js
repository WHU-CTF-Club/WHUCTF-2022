const express = require("express");
const cookieParser = require('cookie-parser');
const laywer = require("./lawyer");

const app = express();
app.use(cookieParser());
app.use(express.urlencoded({extended:false}));

const PORT = process.env.PORT || 9988;

const headers = (req, res, next) => {
    res.setHeader('X-Frame-Options', 'DENY');
    res.setHeader('X-Content-Type-Options', 'nosniff');
    return next();
  }
app.use(headers);
app.use(express.static('public'))

const template = (role) => `
<html>
<head>
<style>
H1 { text-align: center }
H6 { text-align: center }
.center {
    display: block;
    margin-left: auto;
    margin-right: auto;
    width: 50%;
  }

  body {
    place-content:center;
    background:#111;
  }

  * {
    color:white;
  }

</style>
</head>
${role === '' ? '': `<h1> ${role} </h1><a href=/changerole><h6>切换马甲</h6></a>`}
${`<img src='/img/kun${role === 'ikun' ? 1 : 2}.png' width='400' height='700' class='center'></img>`}

<form action="/report" method=POST style="text-align: center;">
  <br>
  <label for="url">有小黑子？举报向对方发送律师函！</label>
  <br>
  <input type="text" id="site" name="url" style-"height:300">
  <input type="submit" value="发送" style="color:black">
</form>
</html>
`;


app.get('/', (req, res) => {
    if (req.cookies.role){
        //construct object
        let finalrole = {
            role: req.cookies.role,
        };
        res.send(template(finalrole.role));
    } else {
        const initialrole = 'ikun';
        res.cookie('role', initialrole, {
            httpOnly: true
        });
        res.redirect('/');
    }
});

app.get('/changerole', (req, res) => {
    res.cookie('role', req.query.newrole ? req.query.newrole : '小黑子', {
        httpOnly: true
    });
    res.redirect('/');
});

app.post('/report', (req, res) => {
    const url = req.body.url;
    laywer.visit(url);
    res.send('已发送！\n绝不原谅鸡脚!');
});

app.listen(PORT, () => console.log((new Date())+`: Web/honksay server listening on port ${PORT}`));
