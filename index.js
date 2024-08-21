const canvas = document.getElementById('canvas');
const canvasContext = canvas.getContext('2d');

let running = true;
var pressedKeys = {};
window.onkeyup = function(e) { pressedKeys[e.key] = false; }
window.onkeydown = function(e) { pressedKeys[e.key] = true; }

Module.onRuntimeInitialized = () => {
    console.log('Module loading...');
    _setup_scene();
    console.log("Module loaded and scene set up.");
    console.log("Starting main loop");
    loop();
}

document.addEventListener('keydown', (event) => {
    if (event.key == 'p') {
        running = !running;
    }
});

function setCanvasImage() {
    const imageData = canvasContext.createImageData(500, 500);
    const buffer_data = _get_buffer();
    var uint8array = new Uint8ClampedArray(Module.HEAPU8.buffer, buffer_data, 500 * 500 * 4);
    imageData.data.set(uint8array);
    canvasContext.putImageData(imageData, 0, 0);
}

function processInput() {
    // INFO FOR _user_input:
    // user_input(int cameraMoveFoward, int cameraMoveSide, int cameraMoveUp, int cameraRotateZ, int cameraRotateY)
    if (pressedKeys['w']) {
        _user_input(1, 0, 0, 0, 0);
    }
    if (pressedKeys['s']) {
        _user_input(-1, 0, 0, 0, 0);
    }
    if (pressedKeys['a']) {
        _user_input(0, -1, 0, 0, 0);
    }
    if (pressedKeys['d']) {
        _user_input(0, 1, 0, 0, 0);
    }
    if (pressedKeys[' ']) {
        renderNeeded = true;
        _user_input(0, 0, 1, 0, 0);
    }
    if (pressedKeys['Shift']) {
        renderNeeded = true;
        _user_input(0, 0, -1, 0, 0);
    }

    if (pressedKeys['ArrowLeft']) {
        renderNeeded = true;
        _user_input(0, 0, 0, 1, 0);
    }
    if (pressedKeys['ArrowRight']) {
        renderNeeded = true;
        _user_input(0, 0, 0, -1, 0);
    }
    if (pressedKeys['ArrowUp']) {
        renderNeeded = true;
        _user_input(0, 0, 0, 0, 1);
    }
    if (pressedKeys['ArrowDown']) {
        renderNeeded = true;
        _user_input(0, 0, 0, 0, -1);
    }
}


async function loop() {
    let readyForNextFrame = true;
    while (true) {
        readyForNextFrame = false;
        setTimeout(() => {
            readyForNextFrame = true;
        },40);
        if (running) {
            processInput();
            setCanvasImage();
        }
        // Wait for 40ms before the next frame
        while (!readyForNextFrame) {
            await new Promise(r => setTimeout(r, 1));
        };
    }
}