// read line by line from file
const fs = require('node:fs')

function lessonA (lines) {
  let sum = 0

  for (const line of lines) {
    if (line.length <= 0) {
      continue
    }
    const cardSplit         = line.split(':')
    const numberSplit       = cardSplit[1].trim().split('|')
    const winningNumbersMap = new Map()
    const winningNumbers    = numberSplit[0].trim().split(/\s+/)
    for (const winningNumber of winningNumbers) {
      winningNumbersMap.set(winningNumber, true)
    }
    const ownNumbers = numberSplit[1].trim().split(/\s+/)
    let subsum       = 0
    for (const ownNumber of ownNumbers) {
      if (winningNumbersMap.has(ownNumber)) {
        if (subsum === 0) {
          subsum = 1
        } else {
          subsum = subsum * 2
        }
      }
    }
    sum = sum + subsum
  }
  console.log('Sum: ', sum)
}

function lessonB (lines) {
  const cardMap = new Map()
  for (let i = 1; i < lines.length; i++) {
    cardMap.set(i, 1)
  }
  let j = 1
  for (const line of lines) {
    if (line.length <= 0) {
      continue
    }
    const cardSplit         = line.split(':')
    const numberSplit       = cardSplit[1].trim().split('|')
    const winningNumbersMap = new Map()
    const winningNumbers    = numberSplit[0].trim().split(/\s+/)
    for (const winningNumber of winningNumbers) {
      winningNumbersMap.set(winningNumber, true)
    }
    const ownNumbers = numberSplit[1].trim().split(/\s+/)
    let subsum       = 0
    for (const ownNumber of ownNumbers) {
      if (winningNumbersMap.has(ownNumber)) {
        subsum++
      }
    }
    const copyCount = cardMap.get(j)
    for (let m = j + 1; m < j + 1 + subsum; m++) {
      const currentValue = cardMap.get(m)
      cardMap.set(m, currentValue + (1 * copyCount))
    }

    j++
  }
  let sum = 0
  for (const [key, value] of cardMap) {
    sum = sum + value
  }

  console.log('Sum: ', sum)
}

try {
  const data  = fs.readFileSync('./lesson4-data.txt', 'utf8')
  const lines = data.split('\n')
  // lessonA(lines)
  lessonB(lines)

} catch (err) {
  console.error(err)
}
