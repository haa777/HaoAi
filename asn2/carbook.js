function validateForm() {
    
    var correct=1;
    var brand = document.getElementById("brand").value;
    if (brand==null||brand=="") {
        correct =0;
    }
    yearrule = /^[0-9]{4}$/;
    var year = document.getElementById("year").value;
    if (!year.match(yearrule)) {
     correct =0;
    }

    var type = document.getElementById("type").value
    if (type==null||type=="") {
        correct =0;
    }
    
    var id = document.getElementById("id").value
    if (id==null||id=="") {
        correct =0;
    }

    var condition = document.getElementById("condition").value
    if (condition==null||condition=="") {
        correct =0;
    }
    var accident = document.getElementById("accident").value
    if (accident==null||accident=="") {
        correct =0;
    }




    var oldlname = document.getElementById("oldlname").value
    if (oldlname==null||oldlname=="") {
        correct =0;
    }
    var oldfname = document.getElementById("oldfname").value
    if (oldfname==null||oldfname=="") {
        correct =0;
    }

    var newlname = document.getElementById("newlname").value
    if (newlname==null||newlname=="") {
        correct =0;
    }
    var newfname = document.getElementById("newfname").value
    if (newfname==null||newfname=="") {
        correct =0;
    }


    cell=/^[0-9]{10}$/;
    var oldcell=document.getElementById("oldcell").value;
    if (!oldcell.match(cell)) {
     correct =0;
    }

    var newcell=document.getElementById("newcell").value;
    if (!newcell.match(cell)) {
     correct =0;
    }

    if (correct==0){
      alert("Complete your information");
    }


}