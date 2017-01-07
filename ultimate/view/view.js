/**
 * Created by lyl_cs on 2016/10/16.
 */
var player1={"name":" ","marker":" ","playNum":1};
var player2={"name":" ","marker":" ","playNum":2};
var currentPlayer=player1;
var allPlayers=new Array();
var tables=new Array();
var currentBoard=null;
var newGame=false;

$(document).ready(function(){
    getAllPlayers();
	for(var i=0;i<9;i++){
		var id="#"+i;
		$(id).addClass("active");
	} 
});

function setSelection(row,col,outerrow,outercol,ele){
    if(!newGame){
        alarm("please start new game!")
        return;
    }
	
	var gridNum=outerrow*3+outercol;
	var id="#"+gridNum;
	if(tables[gridNum]==1||!$(id).hasClass("active")){
		alarm("please select the correct board!")
        return;
	}
    var input= {"row":row,"col":col,"outerRow":outerrow,"outerCol":outercol,"int":currentPlayer.playNum};
    var query= {"controllerMethod":"setSelection","player":currentPlayer,"input":input};
    query =JSON.stringify(query);
    $.post("./cgi-bin/ttt.cgi",query,function(data,status){
        if(data==1){
			$("#alert").html("");
            var i = row*3+col;
            $(ele).children("span").text(currentPlayer.marker);
           determineSubWinner(outerrow,outercol);
           setTable(row,col);
            if(currentPlayer==player1){
                currentPlayer=player2;
            }else{
                currentPlayer=player1;
            }
        }else{
            alarm("wrong set selection");
        }
    });
}

function setTable(row,col){

	for(var i=0;i<9;i++){
		var id="#"+i;
		$(id).css("border-style","inherit");
		$(id).removeClass("active");
	} 
	var gridNum=row*3+col;
	id="#"+gridNum;
    if (tables[gridNum]!=1){   
		$(id).addClass("active");
        $(id).css("border-style","solid");	
    }else{
		for(var i=0;i<9;i++){
		var id="#"+i;
		$(id).addClass("active");
		}
	}
}

function determineSubWinner(outerrow,outercol){
    var gridNum=outerrow*3+outercol;
    var query= {"controllerMethod":"determineSubWinner","player":currentPlayer,"input":{"gridNum":gridNum}};
    query =JSON.stringify(query);

    $.post("./cgi-bin/ttt.cgi",query,function(data,status){
        if(data!=0){
            //block this sub table;
            tables[gridNum] = 1;
            determineWinner();
        }
    });
}

function determineWinner(){

    var query= {"controllerMethod":"determineWinner","player":player1,"player2":player2};
    query =JSON.stringify(query);
    $.post("./cgi-bin/ttt.cgi",query,function(data,status){
        if(data==1){
            alarm(player1.name+" wins");
			var win=parseInt($("#record1").find("li:eq(0) span").text())+1;
			$("#record1").find("li:eq(0) span").text(win);
			var lose=parseInt($("#record2").find("li:eq(1) span").text())+1;
			$("#record2").find("li:eq(1) span").text(lose);
            newGame=false;
        }else if(data==2){
            alarm(player2.name+" wins");
			var lose=parseInt($("#record1").find("li:eq(1) span").text())+1;
			$("#record1").find("li:eq(1) span").text(lose);
			var win=parseInt($("#record2").find("li:eq(0) span").text())+1;
			$("#record2").find("li:eq(0) span").text(win);
            newGame=false;
        } else if(data==3){
            alarm("nobody wins");
			var tie1=parseInt($("#record1").find("li:eq(2) span").text())+1;
			$("#record1").find("li:eq(2) span").text(tie1);
			var tie2=parseInt($("#record2").find("li:eq(2) span").text())+1;
			$("#record2").find("li:eq(2) span").text(tie2);
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
        $("#player1").append("<option value='{\"name\":\""+player.name+"\",\"marker\":\""+player.marker+"\",\"utie\":"+player.stats.utie+",\"ulose\":"+player.stats.ulose+",\"uwin\":"+player.stats.uwin+"}'>"+player.name+" : "+player.marker+"</option>");
        $("#player2").append("<option value='{\"name\":\""+player.name+"\",\"marker\":\""+player.marker+"\",\"utie\":"+player.stats.utie+",\"ulose\":"+player.stats.ulose+",\"uwin\":"+player.stats.uwin+"}'>"+player.name+" : "+player.marker+"</option>");

    })
});
}
function setForm(input){
    var val =JSON.parse( $(input).val());
    if($(input).attr("id")=="player1"){
         if((val.name==player2.name)&&(val.marker==player2.marker)) {
            alarm("cannot be the same name and marker!");
             return;
         }
         $("#name1").val(val.name);
         $("#marker1").val(val.marker);
        $("#record1").find("li:eq(0) span").text(val.uwin);
        $("#record1").find("li:eq(1) span").text(val.ulose);
        $("#record1").find("li:eq(2) span").text(val.utie);
     }else{
         if((val.name==player1.name)&&(val.marker==player1.marker)){
             alarm("cannot be the same name and marker!");
             return;
         }
         $("#name2").val(val.name);
         $("#marker2").val(val.marker);
        $("#record2").find("li:eq(0) span").text(val.uwin);
        $("#record2").find("li:eq(1) span").text(val.ulose);
        $("#record2").find("li:eq(2) span").text(val.utie);
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
        $("span.set").text("");
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
