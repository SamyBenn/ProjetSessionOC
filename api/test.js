const express = require('express')
const app = express()
const mongoClient = require('mongodb').MongoClient
const url = "mongodb://localhost:27017/"

app.use(express.json())

app.use((req, res, next) =>{
console.log('request from '+req.ip+' to '+req.path)
next()
})

app.get("/", (req, res) => { res.send("do that again but this time try asking for some data, /woods for all woods list, /woodInfo/(insert name) for information about that wood.")})

app.get("/data", (req, res) => {
  res.send("What did you expect would happen? now I just have your ip address: "+req.ip+" ... and port: "+req.port)
})

//app.use((req, res, next) =>{})

app.get("/woods", (req, res) => {
  mongoClient.connect(url, function(err, db) {
    if (err) throw err
    var dbo = db.db("meublesDube")
    dbo.collection("wood").find({},{projection: {name:1}}).toArray(function(err, result) {
      if (err) throw err
      //console.log(result)
      res.send(result)
    db.close()
    })
  })
})

app.get("/woodInfo/name=:name", (req, res) => {
  mongoClient.connect(url, function(err, db) {
    if (err) throw err
    var wood = req.params.name
    var dbo = db.db("meublesDube")
    dbo.collection("wood").findOne({name:wood}, function(err, result) {
      if (err) throw err
      //console.log(result)
      res.send(result)
      db.close()
    })
  })
})

app.get("/woodsFull", (req, res) => {
  mongoClient.connect(url, function(err, db) {
    if (err) throw err
    var dbo = db.db("meublesDube")
    dbo.collection("wood").find({}).toArray(function(err, result) {
      if (err) throw err
      //console.log(result)
      res.send(result)
    db.close()
    })
  })
})

app.get("/wood", (req,res)=>{res.redirect("/woods")})

app.get("/woodsInfo/:name", (req,res)=>{
  var oui = req.params.name
  console.log(oui)
  res.send(oui)
})

app.get("/alan", (req,res)=>{
  res.send("C'est le meilleur prof")
})


app.use((req,res)=>{
  res.status(404)
  res.send("<title>IDK</title><h1>Not Found</h1><p>Idk man I've never heard of that place...</p>")
})

app.listen(3001, () => console.log('Server Started'))

