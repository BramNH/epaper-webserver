const char html_input_page[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="" method="GET">
    <p>
      Naam: <input type="text" id="name" name="name"/><br><br>
      Datum: <input type="date" id="date" name="date"/> <br><br>
      Reden: <input type="text" id="reason" name="reason"/><br><br>
      <button type="submit">Submit</button>
    </p>
  </form>
  <br>
</body></html>)rawliteral";

const char html_confirm_page[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<body>
  <h1>Updating E-Paper display, redirecting afterwards...</h1>
  <p>If you are not redirected after E-Paper update, <a href='/'>click here</a>.</p>
  <script>
    setTimeout(function(){ window.location.href = '/'; }, 5000);
  </script>
</body>
</html>)rawliteral";


