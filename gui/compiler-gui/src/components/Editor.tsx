import React, { useRef } from 'react'
import Editor, { OnMount } from '@monaco-editor/react'

interface MonacoEditorProps {
  language?: string
  value?: string
  onChange: (value: string) => void

}

const CustomEditor: React.FC<MonacoEditorProps> = ({
  language = 'typescript',
  value = '// write your code here',
  onChange = (value: string) => {}
}) => {
  const editorRef = useRef<Parameters<OnMount>[0] | null>(null)

  const handleEditorDidMount: OnMount = (editor, monaco) => {
    editorRef.current = editor

    monaco.editor.defineTheme('my-dark', {
      base: 'vs-dark',
      inherit: true,
      rules: [],
      colors: {},
    })
    monaco.editor.setTheme('my-dark')
  }

  return (
    <div className="editor-container">
      <Editor
        height="100vh"
        defaultLanguage={language}
        defaultValue={value}
        onMount={handleEditorDidMount}
        onChange={(str) => {
          str && onChange(str);
        }}
        options={{
          fontSize: 16,
          minimap: {
            enabled: false,
          },
          lineNumbers: 'on',
          automaticLayout: true,
          theme: 'my-dark',
        }}
      />
    </div>
  )
}

export default CustomEditor;