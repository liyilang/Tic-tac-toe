/**
 * Created by lyl_cs on 2016/10/16.
 */
var player1={"name":" ","marker":" ","playNum":1};
var player2={"name":" ","marker":" ","playNum":2};
var currentPlayer=player1;
var grid =  new Array(9);
var allPlayers=new Array();
var newGame=false;

$(document).ready(function(){
    getAllPlayers();
});

function setSelection(row,col,ele){
    if(!newGame){
        alarm("please start new game!")
        return;
    }
    var input= {"row":row,"col":col,"playNum":currentPlayer.playNum};
    var query= {"controllerMethod":"setSelection","player":currentPlayer,"input":input};
    query =JSON.stringify(query);
    $.post("./cgi-bin/ttt.cgi",query,function(data,status){
        if(data==1){
            var i = row*3+col;
            grid[i] = currentPlayer.marker;
            $(ele).children("span").text(currentPlayer.marker);
            if(currentPlayer==player1){

                currentPlayer=player2;
            }else{
                currentPlayer=player1;
            }
            determineWinner();

        }else{
            alarm("wrong set selection");
        }
    });
}

function determineWinner(){

    var query= {"controllerMethod":"determineWinner","player":player1,"input":""};
    query =JSON.stringify(query);
    $.post("./cgi-bin/ttt.cgi",query,function(data,status){
        if(data==1){
            alarm(player1.name+" wins");
            newGame=false;
        }else if(data==2){
            alarm(player2.name+" wins");
            newGame=false;
        } else if(data==3){
            alarm("nobody wins");
            newGame=false;
        }else{
            return;
        }

    });
}
function getAllPlayers(){

    var query= {"controllerMethod":"getAllPlayers","player":player1,"input":""};
    query =JSON.stringify(query);
    $.post("./cgi-bin/ttt.cgi",query,function(data,status){
    allPlayers = JSON.parse(data);
    $.each(allPlayers.players,function(i, player){
        $("#player1").append("<option value='{\"name\":\""+player.name+"\",\"marker\":\""+player.marker+"\"}'>"+player.name+" : "+player.marker+"</option>");
        $("#player2").append("<option value='{\"name\":\""+player.name+"\",\"marker\":\""+player.marker+"\"}'>"+player.name+" : "+player.marker+"</option>");

    })
});
}
function setForm(input){
    var val =JSON.parse( $(input).val());
    newGame=false;
    if($(input).attr("id")=="player1"){
         if((val.name==player2.name)&&(val.marker==player2.marker)) {
            alarm("cannot be the same name and marker!");
             return;
         }
         $("#name1").val(val.name);
         $("#marker1").val(val.marker);
     }else{
         if((val.name==player1.name)&&(val.marker==player1.marker)){
             alarm("cannot be the same name and marker!");
             return;
         }
         $("#name2").val(val.name);
         $("#marker2").val(val.marker);
     }

    }

function submit(){

        var isnull=(($("#marker1").val()=="")||($("#marker2").val()=="")||($("#name1").val()=="")||($("#name2").val()==""));
        if(isnull){
            alarm("cannot be null!");
            return;
        }

        if($("#marker1").val()==$("#marker2").val()) {
            alarm("cannot be the same marker!");
            return;
        }
        player1.name=$("#name1").val();
        player1.marker=$("#marker1").val();
        createPlayer(player1);
        $("#panel1").attr("disabled");

        if(($("#name2").val()==player1.name)&&($("#marker2").val()==player1.marker)){
            alarm("cannot be the same name and marker!");
            return;
        }
        player2.name=$("#name2").val();
        player2.marker=$("#marker2").val();
        createPlayer(player2);
        $("#panel2").attr("disabled");

    var query= {"controllerMethod":"startNewGame","player":player1,"input":""};
    query =JSON.stringify(query);
    $.post("./cgi-bin/ttt.cgi",query,function(data,status){
        currentPlayer =player1;
        $("span").text("");
        $("#alert").html("");
        newGame=true;
    });

}

function createPlayer(player){
    var query= {"controllerMethod":"createPlayer","player":player,"input":player};
    query =JSON.stringify(query);
    $.post("./cgi-bin/ttt.cgi",query,function(data,status){
    });


}

function  alarm(input){
    $("#alert").html('<div onclick="$(this).remove()" style="font-size:x-large" class="alert alert-danger" role="alert">'+input+'</div>');
}
