/* Buttons (Door, Humidifier, LED)*/
function addEventListenerByTagName(tagName, event, fn) {
    var list = document.getElementsByTagName(tagName);
    for (var i = 0, len = list.length; i < len; i++) {
        list[i].addEventListener(event, fn, false);
    }
}

function clickButton() {
    const id = this.id;

    this.className = "waiting";
    this.querySelector("p").innerHTML = "waiting";
    this.setAttribute("disabled", "");

    /* AJAX */
    let httpRequest = new XMLHttpRequest();

    if (!httpRequest)
        console.log("XMLHTTP instance cannot be initialized.")

    httpRequest.onreadystatechange = function () {
        if (this.readyState === 4 && this.status === 200) {
            const res = (httpRequest.responseText === "1") ? "on" : "off";
            let status = "";

            switch (id) {
                case "Door":
                    document.querySelector(`button#${id}`).className = (res === "on") ? "lock" : "unlock";
                    status = (res === "on") ? "Lock" : "Unlock";
                    break;
                case "Humidifier":
                case "LED":
                    document.querySelector(`button#${id}`).className = (res === "on") ? "on" : "off";
                    status = (res === "on") ? "On" : "Off";
                    break;
            }

            document.querySelector(`button#${id} p`).innerHTML = status;
            document.querySelector(`button#${id}`).removeAttribute('disabled');
        }
    };

    switch (id) {
        case "Door":
            httpRequest.open('GET', '/door', true);
            break;
        case "Humidifier":
            httpRequest.open('GET', '/humidifier', true);
            break;
        case "LED":
            httpRequest.open('GET', '/led', true);
            break;
    }

    httpRequest.send();
}

addEventListenerByTagName('button', 'click', clickButton);

/* Humidity */
function recvHumidity() {
    let httpRequest = new XMLHttpRequest();
    httpRequest.onreadystatechange = function () {
        if (this.readyState === 4 && this.status === 200) {
            document.querySelector("span#Humidity").innerHTML = httpRequest.responseText;
        }
    }
    httpRequest.open('GET', '/humidity', true);
    httpRequest.send();
}

setInterval(recvHumidity, 10000);

