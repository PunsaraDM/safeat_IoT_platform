const char group15NodeMCUcode[] =
R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <title>Smart Restaurant</title>
  <meta charset="UTF-8"> <!--enabling charset-->
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <script src="https://www.gstatic.com/firebasejs/8.6.8/firebase-app.js"></script>
  <script src="https://www.gstatic.com/firebasejs/8.6.8/firebase-auth.js"></script>
  <script src="https://www.gstatic.com/firebasejs/8.6.8/firebase-database.js"></script>
  <script src="https://www.gstatic.com/firebasejs/8.6.8/firebase-firestore.js"></script>
  <script src="https://www.gstatic.com/firebasejs/8.6.8/firebase-storage.js"></script>
  <link rel="shortcut icon" type="image/jpg" href="https://firebasestorage.googleapis.com/v0/b/fir-demo-258cc.appspot.com/o/favicon.ico?alt=media&token=71c6716c-35cc-4e27-ac33-c6380c8754f5">
  <style>
    @import url('https://fonts.googleapis.com/css2?family=Open+Sans:wght@300&display=swap');

    *{
        margin: 0px;
        padding: 0px;
        box-sizing: border-box;
    }
    body{
        margin: 10px;
        padding: 0;
        justify-content: center;
        align-items: center;
        background-color: #040f0f;
    }

    h1{
        color: #289944;
        text-align: center;
        font-family: 'Open Sans', sans-serif;
        font-size: 4vh;
    }
    #table-no{
        width: 70%;
        background-color: #656665;
        color: #e8e8e9;
        font-family: 'Open Sans', sans-serif;
        font-weight: bold;
        display: flex;
        justify-content: space-around; 
        margin: auto;
        padding: 10px 20px 10px 20px;  
        border-radius: 10px;
    }
    #table{
        width: 100px;
    }

    #menu{
        margin: auto;
        color: #e8e8e9;
        text-align: center;
        width: 90%;
        background-color: #289944;
        border-radius: 30px;
    }

    .item-card{
        margin: 20px 0 20px 0;
        background-color: #040f0f;
        display: block;
        padding: 20px;
        border-radius: 25px;
    }

    .item-card input, button{
        height: 50px;
        width: 60px;
        align-items: center;
    }

    .item-card button{
        background-color: #e2ba07;
        color: #040f0f;
        font-family: 'Open Sans', sans-serif;
        font-weight: bolder;
    }
    #item-list{
        width: 90%;
        text-align: center;
        justify-content: space-around;
        margin: auto;
        padding: 20px;
    }

    .itemName{
        font-weight: bolder;
        font-family: 'Open Sans', sans-serif;
        font-size: 3vh;
    }

    .itemPrice{
        font-weight: bolder;
        font-family: 'Open Sans', sans-serif;
        font-size: 2vh;
        color: #898d89;
    }

    #orderlist{
        margin: auto;
        color: #e8e8e9;
        text-align: center;
        width: 80%;
        background-color: #0e3013;
        border-radius: 30px;
        padding: 40px;
        font-family: 'Open Sans', sans-serif;
    }

    #orderlist li{
        text-decoration: none;
        list-style: none;
    }

    #orderlist button{
        width: 40%;
        height: 50px;
        background-color: #e2ba07;
        font-family: 'Open Sans', sans-serif;
        color: #040f0f;
        border-radius: 60px;
        font-weight: bolder;
    }


    .itemImage{
        width: 200px;
        height: 200px;
        text-align: center;
        margin: 20px 0 20px 0;
    }

    .heading{
        color: #e8e8e9;
        font-family: 'Open Sans', sans-serif;
        font-size: 6vh;
        text-align: center;
        margin: 20px 0 20px 0;
    }

    #total{
        font-size: 4vh;
        color: #b42906;
        font-family: 'Open Sans', sans-serif;
        text-align: center;
        font-weight: bolder;
    }
  </style>
</head>
<body>
  <h1>WELCOME TO SMART KITCHEN</h1><br>

  <div id="table-no">
    <select name="table" id="table" onchange="select()">
      <option value="select">Select table</option>
      <option value="01">01</option>
      <option value="02">02</option>
      <option value="03">03</option>
    </select>
    <p id="number"></p>
  </div>
  
  <div class="heading">MENU</div>

  <div id="menu">
    <ul id="item-list"></ul>
  </div>

  <div class="heading">ORDER</div>

  <div id="orderlist">
    <p id="number2"></p>
    <ul id="order-list"></ul>
    <div id="total"></div>
    <div id="buttons">
      <button id="reorder" onclick="location.reload()">Re Enter</button><br><br>
      <button id="order" onclick="Order()">Confirm Order</button>
    </div>
    
  </div>

  <audio id="audio5" src="https://firebasestorage.googleapis.com/v0/b/fir-demo-258cc.appspot.com/o/5-minutes.mp3?alt=media&token=ce7ccba9-2719-4490-abe7-94ee6ee5c7e0"></audio>
  <audio id="audio10" src="https://firebasestorage.googleapis.com/v0/b/fir-demo-258cc.appspot.com/o/10-minutes.mp3?alt=media&token=55eedaa5-184f-4ae7-a7ed-0dfaf7d4ea90"></audio>
  <audio id="audio15" src="https://firebasestorage.googleapis.com/v0/b/fir-demo-258cc.appspot.com/o/15-minutes.mp3?alt=media&token=3c0b8a2b-4c20-43e1-9f5a-ca6407b27b09"></audio>
  <audio id="audio20" src="https://firebasestorage.googleapis.com/v0/b/fir-demo-258cc.appspot.com/o/20-minutes.mp3?alt=media&token=57ebe9fc-7875-4196-b727-998d2444f62b"></audio>
  <audio id="orderReady" src="https://firebasestorage.googleapis.com/v0/b/fir-demo-258cc.appspot.com/o/order-ready.mp3?alt=media&token=10c8a4af-5a17-4051-aad9-3622270a67b9"></audio>
  
  
<!-- ---------------------------------------Firebase configuration------------------------------------------------ -->

  <script id="mainscript">
    var firebaseConfig = {
        apiKey: "AIzaSyDsuzKxNyvGmUpv74MYy23T08sEzia1IBo",
        authDomain: "fir-demo-258cc.firebaseapp.com",
        databaseURL: "https://fir-demo-258cc-default-rtdb.firebaseio.com",
        projectId: "fir-demo-258cc",
        storageBucket: "fir-demo-258cc.appspot.com",
        messagingSenderId: "1090395788522",
        appId: "1:1090395788522:web:2b2ce9c5199252c345f393"
    };
    // Initialize Firebase
    firebase.initializeApp(firebaseConfig);
    const db = firebase.firestore(); //firebase firestore
    const rt = firebase.database(); //firebase realtime database
  </script>

<!-- ---------------------------------------------Javascript functions------------------------------------------------- -->
  <script>
    const itemList = document.querySelector('#item-list'); //menu
    const orderList = document.querySelector('#order-list'); //order description
    var order = []; //the final order array
    let total = 0; //the total amount of the order
    let ordered = false;
    let tablename;
    let audio5 = document.getElementById('audio5');
    let audio10 = document.getElementById('audio10');
    let audio15 = document.getElementById('audio15');
    let audio20 = document.getElementById('audio20');

    // ---------------------incrementing the sale------------------
    function incrementSale(){
      let intSale;
      let newSale;

      rt.ref('sale').once('value', snap => {
        intSale = snap.val();
        newSale = intSale + total;
        console.log(newSale);  
        rt.ref('sale').set(newSale);
      });
    }

    // -------------selecting table-----------------
    let table;
    function select(){
      table = document.getElementById('table').value;
      tablename = "table_" + table;
      document.querySelector('#number').innerHTML = "Table " + table;
      document.querySelector('#number2').innerHTML = "Table " + table;
        rt.ref('notifications/'+tablename).on('value', snap => {
          if(ordered==true){
            switch(snap.val()){
              case 5:
                audio5.play();
                window.alert("Your order will be ready in " + snap.val() + " minutes.");
                break;
              case 10:
                audio10.play();
                window.alert("Your order will be ready in " + snap.val() + " minutes.");
                break;
              case 15:
                audio15.play();
                window.alert("Your order will be ready in " + snap.val() + " minutes.");
                break;
              case 20:
                audio20.play();
                window.alert("Your order will be ready in " + snap.val() + " minutes.");
                break;
              case 1:
                orderReady.play();
                window.alert("Your order is ready. Please collect it from the counter");
                break;
            }
            
          }else{
            console.log(snap.val());
          }
        }); 
    }
    
    // ----------------------------------- adding items ---------------------------------------------
    function addItem(querry, doc, id){
      const item = document.querySelector(querry);
      var cost = 0;
      item.addEventListener('submit', (e) => {
          e.preventDefault();
          if(item.quantity.value != ''){
            cost = parseInt(doc.data().price) * parseInt(item.quantity.value);
            if(isNaN(cost)){
              window.alert("Please enter a valid value");
            }else{
              total += cost;
              order.push({
                dish: doc.data().name,
                quantity: item.quantity.value,
                id: id,
                icon: doc.data().image,
                unit_price: doc.data().price,
                item_price: parseInt(doc.data().price) * parseInt(item.quantity.value),
                ingredients: doc.data().ingredients
              });
              document.getElementById('total').innerHTML = "Rs." + total;
              console.log(order);
              let li = document.createElement('li');
              let name = document.createElement('span');
              let quantity = document.createElement('span');
              let price = document.createElement('span');
              name.textContent = doc.data().name + " x ";
              quantity.textContent = item.quantity.value + " = ";
              price.textContent = "Rs." + cost;
              li.appendChild(name);
              li.appendChild(quantity);
              li.appendChild(price);

              orderList.appendChild(li);
              item.quantity.value = '';
            }
          }else{
            window.alert("Please add the quantity first");
          }
      });
      
    }

    // ------------------------------------- viewing items --------------------------------------------
    function renderItems(doc){
      let form = document.createElement('form');
      let name = document.createElement('label');
      let price = document.createElement('label');
      let img = document.createElement('img');
      let q = document.createElement('input');
      let b = document.createElement('button');
      let br1 = document.createElement('br');
      let br2 = document.createElement('br');
      let br3 = document.createElement('br');
      let itemId = "item"+doc.id;
      let querry = '#'+itemId;
      form.setAttribute('id', itemId);
      form.setAttribute('class', "item-card")
      name.setAttribute('class',"itemName");
      price.setAttribute('class',"itemPrice");
      img.setAttribute('class', "itemImage");
      img.setAttribute('src', doc.data().image);
      q.setAttribute('id', doc.id);
      q.setAttribute('placeholder', "Quantity");
      q.setAttribute('name', "quantity");
      b.innerHTML = "ADD";
      name.textContent = doc.data().name;
      price.textContent =  "Rs." + doc.data().price;

      form.appendChild(name);
      form.appendChild(br1);
      form.appendChild(price);
      form.appendChild(br2);
      form.appendChild(img);
      form.appendChild(br3);
      form.appendChild(q);
      form.appendChild(b);

      itemList.appendChild(form);
      
      addItem(querry, doc, doc.id);
    }

    db.collection('items').get().then((snapshot) => {
      snapshot.docs.forEach( doc => {
        renderItems(doc);
      })
    });

    // --------------------------------------confirming the order-----------------------------
    function Order(){
      let tablename;
      tablename = "table_" + table;
      if(table != "select" && table != undefined){
        window.confirm("Are you sure ?");
        rt.ref('orders/'+tablename).set({
          table: table,
          order,
          total: total
        });
        incrementSale();
        setTimeout(() => {
          document.getElementById('buttons').innerHTML = "Your order has been recorded";
          ordered = true;
        },2000);    
      }else{
        window.alert("Please enter the Table Number")
      }
      
    }
    
  </script>

</body>

</html>
)=====";
