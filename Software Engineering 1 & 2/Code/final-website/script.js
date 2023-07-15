const wrapper = document.querySelector('.wrapper');
const loginLink = document.querySelector('.login-link');
const registerLink = document.querySelector('.register-link');
const btnPopup = document.querySelector('.create');
const logbtn = document.getElementById('btnn');

registerLink.addEventListener('click', () => {
    wrapper.classList.add('active');
});

loginLink.addEventListener('click', () => {
    wrapper.classList.remove('active');
});

logbtn.addEventListener("click", () => {
    window.location.href = "map.html";
});

function goToURL() {
    window.open('map.html');
}