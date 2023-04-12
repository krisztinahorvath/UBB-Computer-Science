$(document).ready(function (){
    var imageWidth = 240;
    var position = 0;
    var popDiv = document.getElementById("popDiv");
    var popImg = document.getElementById("popImg");

    // row of images
    $("li").each(function(){
        position += imageWidth;
        $(this).css("left", position);
    });

    $("img").click(function(){
        // the img that was clicked
        let img = $(this).attr('src');

        // pop-up img
        popDiv.style.display = 'block';

        // source of the pop-up img
        popImg.src = img;

        // stop sliding
        $("li").stop(true);
    });

    popImg.onclick = function(){
        // if pop-up img clicked, hide it
        popDiv.style.display = 'none';
        slide();
    }

    function slide(){
        // move pictures to the left with 10px to make them slide continuously
        $("li").animate({"left":"+=10px"}, 100, again);
    }

    function again(){
        //  current pos of the left edge of the img relative to the left edge of the document
        let left = $(this).parent().offset().left + $(this).offset().left;

        // make the img come back on the opposite side
        if (left >= 1920) { // 1430
            $(this).css("left",left - 1920);
        }
        slide();
    }

    // make it slide when you open the site
    slide();

});