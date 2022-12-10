const mongoose = require('mongoose')

const woodSchema = new mongoose.Schema({name:{type: String}},{type:{type:String}},{origine:{type:String}},{drying:{type:Number}})

module.exports = mongoose.model('wood', woodSchema)
