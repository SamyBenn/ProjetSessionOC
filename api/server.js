const express = require('express')
const app = express()
const mongoClient = require('mongodb').MongoClient
const url = "mongodb://localhost:27017/"

app.use(express.json())

app.use((req, res, next) =>{
console.log('request from ', req.url, ' to ', req.path)
next()
})

app.get("/", (req, res) => { res.send("do that again but this time try asking for some data, /api/woods for all woods list, /api/woodInfo/(insert name) for information about that wood.")})

app.get("/woods", (req, res) => {
  mongoClient.connect(url, function(err, db) {
    if (err) throw err
    var dbo = db.db("meublesDube")
    dbo.collection("woods").find({},{projection: {name:1}}).toArray(function(err, result) {
      if (err) throw err
      console.log(result)
      res.json(result)
    db.close()
    })
  })
})

app.get("/woodsFull", (req, res) => {
  mongoClient.connect(url, function(err, db) {
    if (err) throw err
    var dbo = db.db("meublesDube")
    dbo.collection("woods").find({}).toArray(function(err, result) {
      if (err) throw err
      console.log(result)
      res.send(result)
    db.close()
    })
  })
})

app.get("/woodInfo/:name", (req, res) => {
  mongoClient.connect(url, function(err, db) {
    if (err) throw err
    var wood = req.params.name
    var dbo = db.db("meublesDube")
    dbo.collection("woods").findOne({name:wood}, function(err, result) {
      if (err) throw err
      console.log(result)
      res.send(result)
      db.close()
    })
  })
})

app.listen(3000, () => console.log('Server Started'))

