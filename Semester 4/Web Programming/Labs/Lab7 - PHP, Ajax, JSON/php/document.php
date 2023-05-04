<?php
    class Document implements JsonSerializable {
        private $id;
        private $title;
        private $author;
        private $numberOfPages;
        private $type;
        private $format;

        function __construct($id, $title, $author, $numberPages, $type, $format)
        {
            $this->id = $id;
            $this->title = $title;
            $this->author = $author;
            $this->numberOfPages = $numberPages;
            $this->type = $type;
            $this->format = $format;
        }

        public function get_id(){
            return $this->id;
        }

        public function set_id($newId): void
        {
            $this->id = $newId;
        }

        public function get_title(){
            return $this->title;
        }

        public function set_title($newTitle): void
        {
            $this->title = $newTitle;
        }

        public function get_author(){
            return $this->author;
        }

        public function set_author($newAuthor): void
        {
            $this->author = $newAuthor;
        }

        public function get_numberOfPages(){
            return $this->numberOfPages;
        }

        public function set_numberOfPages($newNumberPages): void
        {
            $this->numberOfPages = $newNumberPages;
        }

        function get_type(){
            return $this->type;
        }

        public function set_type($newType): void
        {
            $this->type = $newType;
        }

        public function get_format(){
            return $this->format;
        }

        public function set_format($newFormat): void{
            $this->format = $newFormat;
        }

        public function jsonSerialize()
        {
            $vars = get_object_vars($this);
            return $vars;
        }
    }






