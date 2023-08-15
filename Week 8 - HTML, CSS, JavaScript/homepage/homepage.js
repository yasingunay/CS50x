// This line adds an event listener to the "DOMContentLoaded" event, which is triggered when the HTML document's initial structure and content have been fully loaded and parsed.
document.addEventListener("DOMContentLoaded", function () {

    // This variable stores a reference to the HTML element with the ID "menuContainer".
    var menuContainer = document.getElementById("menuContainer");

    // This line initiates a fetch request to the "menu.html" file. The fetch function returns a Promise that represents the result of the request.
    fetch("menu.html")

      // This part of the code chain is executed when the fetch request successfully resolves. It converts the response from the request to text format.
      .then(response => response.text())

      // This part of the code chain is executed after the response text has been extracted. It takes the response text and assigns it as the innerHTML of the "menuContainer" element.
      .then(content => {
        menuContainer.innerHTML = content;
      })

      // This part of the code chain is executed if any errors occur during the fetch request or the subsequent Promise chain. It logs the error to the console.
      .catch(error => console.error(error));

  });


// Greet user
  function greet()
  {
      let name = document.querySelector('#name').value;
      alert('hello ' + name);
  }


// Change background color
  document.addEventListener("DOMContentLoaded", function () {

    let body = document.querySelector('body')
    document.querySelector('#red').addEventListener('click',function(){
        body.style.backgroundColor = 'red';
        alert("Red!");
    });
    document.querySelector('#green').addEventListener('click',function(){
        body.style.backgroundColor = 'green';
        alert("Green!");
    });
    document.querySelector('#blue').addEventListener('click',function(){
        body.style.backgroundColor = 'blue';
        alert("Blue!");
    });
    document.querySelector('#default').addEventListener('click',function(){
        body.style.backgroundColor = 'white';
    });

  });



// Search definiton of the name
  document.addEventListener('DOMContentLoaded', function () {
    const searchButton = document.getElementById('searchButton');
    const nameInput = document.getElementById('name');
    const searchResults = document.getElementById('searchResults');

    searchButton.addEventListener('click', function () {
        const name = nameInput.value;
        if (name.trim() !== '') {
            const googleSearchUrl = `https://www.google.com/search?q=${encodeURIComponent(name)}+definition`;
            window.open(googleSearchUrl, '_blank');
        } else {
            searchResults.innerHTML = 'Please enter a name.';
        }
    });
});



// This code checks if a link is not secure (http) and displays an alert
window.addEventListener("DOMContentLoaded", function() {
  const allLinks = document.querySelectorAll("a");

  allLinks.forEach(link => {
    if (link.href.startsWith("http://")) {
      link.addEventListener("click", function(event) {
        event.preventDefault();
        alert("This link is not secure (HTTP). Are you sure you want to continue?");
      });
    }
  });
});



// Toggles visibility of the button
function blink()
{
  let button = document.querySelector('#blink');
  {
    if (button.style.visibility == 'hidden')
    {
      button.style.visibility = 'visible';
    }
    else
    {
      button.style.visibility = 'hidden';
    }
  }
}


// Call the 'blink' function repeatedly every 50 milliseconds to create a blinking effect
window.setInterval(blink,500);
