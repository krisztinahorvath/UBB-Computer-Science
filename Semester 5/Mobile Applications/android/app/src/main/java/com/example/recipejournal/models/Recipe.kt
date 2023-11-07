package com.example.recipejournal.models

data class Recipe(
    val id: Int,
    var name: String,
    var ingredients: String,
    var directions: String,
    var time: Int,
    var servings: Int
)