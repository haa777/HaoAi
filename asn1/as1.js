function baconShow(){
	var baconAPI = "https://baconipsum.com/api/?type=all-meat&paras=2&start-with-lorem=3&format=json";
			$.getJSON( baconAPI, function( data ) {
				var item = [];
				$.each( data, function( key, val ) {
					item.push( "<p>" + val + "</p>" );
				});
				document.getElementById("baconipsum").innerHTML = item[0]+item[1];
			});

}




$(document).ready(function(){
    $.get("https://randomuser.me/api/", function(data, status){
	var jsonString = JSON.stringify(data);
	var obj = JSON.parse(jsonString);
  $("#title").html("title: " + obj.results[0].user.name.title);
  $("#name").html("name: " + obj.results[0].user.name.first +" "+ obj.results[0].user.name.last)
  $("#gender").html("gender: " + obj.results[0].user.gender);
  $("#street").html("Street: " + obj.results[0].user.location.street);
  $("#city").html("City: " + obj.results[0].user.location.city);
  $("#state").html("State: " + obj.results[0].user.location.state);
  $("#zip").html("Zip: " + obj.results[0].user.location.zip);
  $("#nationality").html("Nationality: " + obj.nationality);

  $("#phone").html("Phone: " + obj.results[0].user.phone);
  $("#cell").html("Cell: " + obj.results[0].user.cell);
  $("#email").html("Email: " + obj.results[0].user.email);
  $("#userPhoto").attr("src", obj.results[0].user.picture.medium);
    });
});


// second page

var lat;
var lng;
function getmap(){
      var aboutmeAPI = "https://randomuser.me/api/";
    $.getJSON( aboutmeAPI, function(data) {
        var address = data.results[0].user.location.street + "+" + data.results[0].user.location.city + "+" + data.results[0].user.location.state;
        address = address.replace(/\s+/g, '+');
        var geocoder = new google.maps.Geocoder();
        var map = new google.maps.Map(document.getElementById('map'), {
          zoom: 9,
          center: {lat: -34.397, lng: 150.644}
      });
      geocodeAddress(geocoder, map, address);
    });
  }
  /* Google Map Initialization */
    var map;
    function initMap() {
      var myaddr = new google.maps.LatLng(lat, lng);
      var map = new google.maps.Map(document.getElementById('map'), {
      zoom: 12,
      center: myaddr
    });
}

  /* Find and tag the specific address in the Google Map */
  function geocodeAddress(geocoder, resultsMap, addr) {
      var address = addr;
      geocoder.geocode({'address': address}, function(results, status) {
        if (status === google.maps.GeocoderStatus.OK) {
          resultsMap.setCenter(results[0].geometry.location);
            var marker = new google.maps.Marker({
            map: resultsMap,
            position: results[0].geometry.location
        });
      }else{
          alert('Geocode was not successful for the following reason: ' + status);
        }
      });
  }


/* Google Map Initialization */
  



function validateForm() {

    var correct=1;
    var n = document.getElementById("name").value;

    if (n==null||n=="") {
        correct =0;
    }
    
    email=/^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    var e=document.getElementById("email").value;
    if (!e.match(email)) {
        correct =0;
    }
    
    cell=/^[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]$/;
    var pn=document.getElementById("pnumber").value;
    if (!pn.match(cell)) {
     correct =0;
    }
    
    daterule= /^(0[1-9]|1[0-2])\/(0[1-9]|1\d|2\d|3[01])\/(19|20)\d{2}$/;
    var date=document.getElementById("date").value;
    if (!date.match(daterule)) {
        correct =0;
    }
   
    var me=document.getElementById("message").value;
    if (me==null||me=="") {
      correct =0;
    }

    if (correct==0){
      alert("Complete your information");
    }else if(correct==1){
      alert("Your information is correct");
    }else{
    	alert("code doesn't work")
    }


}