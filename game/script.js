const canvas = document.getElementById('canvas1');
const ctx = canvas.getContext('2d');
canvas.width = 800;
canvas.height = 500;
const keys = [];

const player = {
    x: 200,
    y: 200,
    width: 32,
    height: 48,
    frameX: 0,
    frameY: 0,
    speed: 9,
    moving: false
};

const playerSprite = new Image();
playerSprite.src = 'player1.png';

const background = new Image();
background.src = 'backgrounddetailed1.png';

function drawSprite(img, sX, sY, sW, sH, dX, dY, dW, dH) {
    ctx.drawImage(img, sX, sY, sW, sH, dX, dY, dW, dH);
}

function animation() {
    // Clear screen
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // Draw background
    ctx.drawImage(background, 0, 0, canvas.width, canvas.height);

    drawSprite(
        playerSprite,
        player.width * player.frameX,
        player.height * player.frameY,
        player.width, player.height,
        player.x, player.y,
        player.width,
        player.height);

    movePlayer();
    // Rerun animation
    requestAnimationFrame(animation);
}

animation();

window.addEventListener("keydown", function(event) {
    let key = event.key;
    keys[event.keyCode] = true;
    console.log(event.key);
    console.log(keys);
});

window.addEventListener("keyup", function(event) {
    delete keys[event.keyCode];
});

function movePlayer() {
    if(keys[38] && player.y > 100) {
        player.y -= player.speed;
    }
}

