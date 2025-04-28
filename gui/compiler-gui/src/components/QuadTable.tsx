import React from 'react'

type ParsedRow =
  | { type: 'label'; label: string }
  | { type: 'quad'
      index: string
      op:    string
      arg1:  string
      arg2:  string
      res:   string
    }

function parseQuadruples(text: string): ParsedRow[] {
  const lines = text
    .split('\n')
    .map((l) => l.trim())
    .filter((l) => l.length > 0)

  const rows: ParsedRow[] = []

  for (const line of lines) {
    // 1) label line (anything ending in a colon or semicolon)
    if (/^[A-Za-z].*[:;]$/.test(line)) {
      rows.push({ type: 'label', label: line })
      continue
    }

    // 2) quad line: [ idx ] ( OP , ARG1 , ARG2 , RES )
    const m = line.match(
      /^\[\s*(\d+)\s*\]\s*\(\s*([^,]+)\s*,\s*([^,]+)\s*,\s*([^,]+)\s*,\s*([^)]+)\)$/
    )
    if (m) {
      rows.push({
        type:  'quad',
        index: m[1].trim(),
        op:    m[2].trim(),
        arg1:  m[3].trim(),
        arg2:  m[4].trim(),
        res:   m[5].trim(),
      })
    }
  }

  return rows
}

const cellStyle: React.CSSProperties = {
  border: '1px solid #555',
  padding: '4px 8px',
  textAlign: 'center',
}
const labelStyle: React.CSSProperties = {
  backgroundColor: '#333',
  color: '#fff',
  fontWeight: 'bold',
  textAlign: 'center',
  padding: '4px 0',
}

interface QuadTableProps {
  raw: string
}

export const QuadTable: React.FC<QuadTableProps> = ({ raw }) => {
  const rows = parseQuadruples(raw)
  const [isRoutine, setIsRoutine] = React.useState(false);

  return (
    <table
      style={{
        width: '100%',
        borderCollapse: 'collapse',
        color: '#fff',
      }}
    >
      <thead>
        <tr>
          <th style={cellStyle}>Index</th>
          <th style={cellStyle}>Op</th>
          <th style={cellStyle}>Arg1</th>
          <th style={cellStyle}>Arg2</th>
          <th style={cellStyle}>Res</th>
        </tr>
      </thead>
      <tbody>
        {rows.map((r, i) =>
          r.type === 'label' ? (
            <tr key={i}>
              <td colSpan={5} style={{border: "1px solid rgb(85, 85, 85)", padding: "10px 20px"}}>
                {r.label}
              </td>
            </tr>
          ) : (
            <tr key={i} style={{background: isRoutine? "#221122" : "#222"}}>
              <td style={cellStyle}>{r.index}</td>
              <td style={cellStyle}>{r.op}</td>
              <td style={cellStyle}>{r.arg1}</td>
              <td style={cellStyle}>{r.arg2}</td>
              <td style={cellStyle}>{r.res}</td>
            </tr>
          )
        )}
      </tbody>
    </table>
  )
}
