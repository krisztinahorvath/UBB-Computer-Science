$(document).ready(function() {
    let startOffset = null;
    let startImg = null;

    $(".puzzle_piece").draggable({
        revert: "invalid",
        start: function(event, ui) {
            startOffset = $(this).offset();
            startImg = $(this);
        }
    });

    $(".puzzle_piece").droppable({
        tolerance: "intersect",
        drop: function(event, ui) {
            let droppedId = ui.draggable.attr("id");
            // let droppedSrc = ui.draggable.attr("src");
            //
            let targetId = $(this).attr("id");
            // let targetSrc = $(this).attr("src");

            let startLeft = startOffset.left;
            let startTop = startOffset.top;
            let endLeft = $(this).offset().left;
            let endTop = $(this).offset().top;

            startImg.offset({ top: endTop, left: endLeft });
            $(this).offset({ top: startTop, left: startLeft });

            $.ajax({
                url: "puzzle",
                type: "PUT",
                data: {
                    "id1": droppedId,
                    "id2": targetId
                },
                success: function (response) {
                    $("#score").html(response);
                }
            });
        }
    });
});
