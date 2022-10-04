const html = document.documentElement;
const body = document.body;
const box = document.querySelector('.box');
let allGoods = document.querySelectorAll('.goods');
const selectLevel = document.querySelector('.selectLevel');
const disorganize = document.querySelector('.disorganize');
const reset = document.querySelector('.reset');
const BGAudio = document.querySelector('.BGAudio');
const audio = document.querySelector('.audio');
const recall = document.querySelector('.recall');
const surplus = document.querySelector('.surplus');
const levelBox = document.querySelector('.levelBox');
const levelBoxDiv = document.querySelector('.levelBox>div');
const levelBoxBtn = document.querySelectorAll('.levelBox>div button');
const chronoscope = document.querySelector('.chronoscope');
let boxGoodsLeft = 0;
let boxVolume = 0;
let spacing = 65;
let disorganizeNum = 3;
let recallNum = 3;
let chronoscopeNum = 0;
let range = 350;

const goodsList = [
    'zoon1', 'zoon2', 'zoon3', 'zoon4', 'zoon5', 'zoon6', 'zoon7', 'zoon8', 'zoon9',
    'fruit1', 'fruit2', 'fruit3', 'fruit4', 'fruit5', 'fruit6', 'fruit7', 'fruit8', 'fruit9',
    'cake1', 'cake2', 'cake3', 'cake4', 'cake5', 'cake6', 'cake7', 'cake8', 'cake9'
]

function randomNum(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

if (/Android|webOS|iPhone|iPod|BlackBerry/i.test(navigator.userAgent)) {
    const equipment = document.querySelector('.equipment');
    equipment.setAttribute('href', 'css/mobile.css');
    spacing = 48;
    range = 0;
}

function createGoods(oneGoods) {
    const goods = document.createElement('div');
    goods.classList.add('goods');
    goods.style.backgroundImage = `url(imgs/${oneGoods}.png)`;
    goods.setAttribute('mark', oneGoods)
    goods.style.top = randomNum(222, window.innerHeight - 333) + 'px';
    goods.style.left = randomNum(20 + range, window.innerWidth - 70 - range) + 'px';
    body.appendChild(goods);
    goods.setAttribute('onclick', 'goodsClick(this)');
}

function goodsClick(self) {
    if (boxVolume >= 7) return;
    createdAudio('audio/点击.mp3');
    const newGoods = self.cloneNode();
    newGoods.style.top = 0;
    newGoods.style.left = boxGoodsLeft + 'px';
    newGoods.style.padding = 0;
    newGoods.removeAttribute('onclick');
    boxGoodsLeft += spacing;
    boxVolume++;
    newGoods.style.opacity = 0;
    box.appendChild(newGoods);
    self.style.transition = 'top .4s, left .4s';
    self.style.padding = 0;
    self.style.top = box.offsetTop + 2 + 'px';
    self.style.left = boxGoodsLeft + box.offsetLeft - self.offsetWidth + 'px';
    setTimeout(() => {
        newGoods.style.opacity = 1;
        self.remove();
    }, 400);
    let count = 0;
    let children = [...box.children];
    children.forEach(item => item.getAttribute('mark') == newGoods.getAttribute('mark') && count++);
    let deleteNum = 3;
    if (count >= 3) {
        createdAudio('audio/得分.mp3');
        surplus.innerText = allGoods.length - 3;
        boxVolume -= 3;
        children.forEach(item => {
            if (item.getAttribute('mark') == newGoods.getAttribute('mark') && deleteNum > 0) {
                deleteNum--;
                item.style.animation = 'fade .3s linear';
                setTimeout(() => {
                    item.remove();
                    children = [...box.children];
                    boxGoodsLeft = spacing * children.length;
                    children.forEach((item, index) => {
                        item.style.transition = 'left .2s';
                        item.style.left = index * spacing + 'px';
                    });
                }, 200);
            }
        });
    }
    boxVolume >= 7 && gameFinish('很遗憾你输了', 'audio/失败.mp3');
    setTimeout(() => {
        allGoods = document.querySelectorAll('.goods');
        if (allGoods.length <= 0) {
            if (chronoscopeNum > 20) {
                gameFinish('太慢啦!', 'audio/失败.mp3');
            } else if (selectLevel.getAttribute('level') == 233) {
                fetch("/fl4g.php",)
                    .then(x=>x.text())
                    .then(x=>gameFinish(`单身就是棒!!!\n离胜利只差一步啦\nHint:${x}`, 'audio/胜利2.mp3'));
            } else {
                gameFinish(`恭喜你通过了${selectLevel.innerText}\n用时${chronoscopeNum}秒\n通过第二关去获取flag吧!`, 'audio/胜利2.mp3');
            }
            const levelRecord = JSON.parse(localStorage.getItem('sheep_level_record'));
            levelRecord[selectLevel.getAttribute('index')]++;
            localStorage.setItem('sheep_level_record', JSON.stringify(levelRecord));
        }
    }, 450);
}

function gameFinish(str, audio) {
    setTimeout(() => {
        alert(str);
        selectLevel.click();
    }, 200);
    surplus.innerText = allGoods.length;
    createdAudio(audio);
    disorganizeNum = 0;
    recallNum = 0;
}

function gameStart(number) {
    boxVolume = 0;
    boxGoodsLeft = 0;
    allGoods = document.querySelectorAll('.goods');
    allGoods.forEach(item => item.remove());
    disorganizeNum = 3;
    disorganize.innerText = `打乱 ${disorganizeNum}`;
    recallNum = 3;
    recall.innerText = `撤回 ${recallNum}`;
    chronoscopeNum = 0;
    chronoscope.innerText = chronoscopeNum;
    for (let i = 0; i < number; i++) {
        const num = randomNum(0, goodsList.length - 1);
        for (let i = 0; i < 3; i++) createGoods(goodsList[num]);
    }
    allGoods = document.querySelectorAll('.goods');
    allGoods.forEach(item => item.style.animation = `enter .3s`);
    surplus.innerText = allGoods.length;
}

disorganize.addEventListener('click', () => {
    if (disorganizeNum <= 0) return;
    disorganizeNum--;
    disorganize.innerText = `打乱 ${disorganizeNum}`;
    allGoods.forEach(item => {
        if (!item.getAttribute('onclick')) return;
        item.style.transition = 'top .4s, left .7s';
        item.style.top = randomNum(222, window.innerHeight - 333) + 'px';
        item.style.left = randomNum(20 + range, window.innerWidth - 70 - range) + 'px';
    });
});
disorganize.innerText = `打乱 ${disorganizeNum}`;

reset.addEventListener('click', () => gameStart(selectLevel.getAttribute('level')));

function createdAudio(src) {
    const audio = document.createElement('audio');
    document.body.appendChild(audio);
    audio.autoplay = true;
    audio.setAttribute('src', src);
    audio.play();
    audio.addEventListener('ended', e => e.target.remove());
}

audio.addEventListener('click', () => {
    if (BGAudio.getAttribute('src')) BGAudio.setAttribute('src', '');
    else BGAudio.setAttribute('src', 'audio/BGM1.mp3');
    BGAudio.play();
});

recall.addEventListener('click', () => {
    let len = box.children.length;
    if (len <= 0 || recallNum <= 0) return;
    recallNum--;
    recall.innerText = `撤回 ${recallNum}`;
    let lastChild = box.children[len - 1];
    const newGoods = lastChild.cloneNode();
    newGoods.style.padding = '23px';
    newGoods.style.top = randomNum(222, window.innerHeight - 333) + 'px';
    newGoods.style.left = randomNum(20 + range, window.innerWidth - 70 - range) + 'px';
    newGoods.setAttribute('onclick', 'goodsClick(this)');
    body.appendChild(newGoods);
    boxGoodsLeft -= spacing;
    boxVolume--;
    lastChild.remove();
});
recall.innerText = `撤回 ${recallNum}`;

selectLevel.addEventListener('click', () => {
    levelBox.style.display = 'block';
    const levelRecord = JSON.parse(localStorage.getItem('sheep_level_record'));
    levelRecord.forEach((item, index) => item && levelBoxBtn[index].classList.add('win'));
});

levelBoxDiv.addEventListener('click', () => levelBox.style.display = 'none');

levelBoxBtn.forEach(item => {
    item.addEventListener('click', e => {
        const level = e.target.getAttribute('level');
        gameStart(level);
        selectLevel.setAttribute('level', level);
        selectLevel.setAttribute('index', e.target.getAttribute('index'));
        selectLevel.innerText = e.target.innerText;
    });
});

const levelRecord = new Array(levelBoxBtn.length);
for (let i = 0; i < levelRecord.length; i++) levelRecord[i] = 0;
localStorage.getItem('sheep_level_record') || localStorage.setItem('sheep_level_record', JSON.stringify(levelRecord));

setInterval(() => chronoscope.innerText = ++chronoscopeNum, 1000);

gameStart(selectLevel.getAttribute('level'));

// cheating
let pressTime = 0;
levelBoxDiv.addEventListener('touchstart', () => pressTime = +new Date());
levelBoxDiv.addEventListener('touchend', () => {
    pressTime = +new Date() - pressTime;
    if (pressTime > 3000) disorganizeNum = 9;
});