import { useEffect, useState } from 'react'
import CustomEditor from "./components/Editor";
import './App.css'
import IconButton from '@mui/material/IconButton';
import { QuadTable } from './components/QuadTable';
import Drawer from '@mui/material/Drawer';
import PlayArrowIcon from '@mui/icons-material/PlayArrow';
import TableChartIcon from '@mui/icons-material/TableChart';
import ErrorOutlineIcon from '@mui/icons-material/ErrorOutline';
import ErrorIcon from '@mui/icons-material/Error';
import WarningIcon from '@mui/icons-material/Warning';
import { Box, Modal, Stack, Typography } from '@mui/material';
import ReactMarkdown from 'react-markdown'
import remarkGfm from 'remark-gfm'

const style = {
  position: 'absolute',
  top: '10%',
  left: '10%',
  height: "90vh",
  overflowY: "auto",
  transform: 'translate(-5%, -5%)',
  width: "90%",
  bgcolor: '#000',
  border: '2px solid #000',
  boxShadow: 24,
  p: 4,
};

function App() {
  const [code, setCode] = useState<string>('// Write your code')
  const [quads, setQuads] = useState<string>('');
  const [st, setST] = useState<string>('');
  const [errAndWarn, setErrAndWarn] = useState<string>('');
  const [open, setOpen] = useState(false);
  const [errorsDrawer, setErrorsDrawer] = useState(false);
  const onClickHandler = async () => {
    try {
      const response = await fetch(`http://localhost:8080/run`, {
        method: 'POST',
        headers: {
          'Content-Type': 'text/plain',
        },
        body: code,
      });
      const result = await response.text();
      console.log(code);
      const sections = result.split(/=== .*? ===/).filter((_, index) => index !== 0);
      const [quadruples, trackedTables, errorsAndWarnings] = sections;
      console.log(sections);

      setQuads(quadruples || '');
      setST(trackedTables || '');
      setErrAndWarn(errorsAndWarnings || '');
    } catch (error) {
      console.error('Error:', error);
    }
  };
  const handleSymbolTablesFetch = () => {
    console.log(code);
    try {
      setOpen(true);
    } catch (error) {
      console.error('Error:', error);
    }
  };
  useEffect(() => {
    const handleKeyDown = (event: KeyboardEvent) => {
      if (event.ctrlKey && event.key === 's') {
        event.preventDefault();
        onClickHandler();
      }
    };

    window.addEventListener('keydown', handleKeyDown);

    return () => {
      window.removeEventListener('keydown', handleKeyDown);
    };
  }, [code, onClickHandler]);

  return (
    <>
      <div style={{ padding: "0 20px" }}>
        <div style={{ position: "fixed", right: "40px", top: "20px", background: "#222", padding: "5px 10px", border: "1px solid #333", borderRadius: "10px" }}>
          <Stack direction="row" spacing={2}>
            <IconButton onClick={() => setErrorsDrawer(true)} sx={{ "&:hover svg": { color: "#2674c2" }, ...(errAndWarn == "\n" ? {} : { backgroundColor: "#ff4d4d" }) }}>
              <ErrorOutlineIcon sx={{ fontSize: "20px", color: "#fff", transition: "all .5s" }} />
            </IconButton>
            <IconButton onClick={handleSymbolTablesFetch} sx={{ "&:hover svg": { color: "#2674c2" } }}>
              <TableChartIcon sx={{ fontSize: "20px", color: "#fff", transition: "all .5s" }} />
            </IconButton>
            <IconButton onClick={onClickHandler} sx={{ "&:hover svg": { color: "#2674c2" } }}>
              <PlayArrowIcon sx={{ fontSize: "20px", color: "#fff", transition: "all .5s" }} />
            </IconButton>
          </Stack>
        </div>
      </div>
      <div style={{ display: "flex" }}>
        <div style={{ backgroundColor: "#222", flex: "1" }}>
          <CustomEditor onChange={setCode} language='cpp' value={code} />
        </div>
        <div id="quads" style={{ backgroundColor: "#222", flex: "1", height: "100vh", padding: "60px 20px" }}>
          <QuadTable raw={quads} />
        </div>
      </div>

      <Modal
        open={open}
        onClose={() => setOpen(false)}
        aria-labelledby="modal-modal-title"
        aria-describedby="modal-modal-description"
      >
        <Box sx={style}>
          <Typography id="modal-modal-title" variant="h6" component="h2">
            Symbol Tables
          </Typography>
          <ReactMarkdown
            remarkPlugins={[remarkGfm]}
          >
            {st}
          </ReactMarkdown>
        </Box>
      </Modal>

      <Drawer
        anchor={'bottom'}
        open={errorsDrawer}
        onClose={() => setErrorsDrawer(false)}
        sx={{ '& .MuiPaper-root': { backgroundColor: "#222", color: "#fff" } }}
      >
        <div style={{ padding: "30px", maxHeight: "50vh", overflowY: "auto" }}>
          {errAndWarn
            .split("\n")
            .map(line => line.trim())
            .filter(line => line) // drop empty lines
            .map((line, idx) => {
              if (line.startsWith("Error:")) {
                return (
                  <>
                    <div key={idx} style={{ display: "flex", alignItems: "center", padding: "10px 0", borderBottom: "1px solid #444" }}>
                      <ErrorIcon sx={{ color: "#ff4d4d", marginRight: "8px" }} />
                      <span>{line}</span>
                    </div>
                  </>
                );
              }
              if (line.startsWith("Warning:")) {
                return (
                  <>
                    <div key={idx} style={{ display: "flex", alignItems: "center", padding: "10px 0", borderBottom: "1px solid #444" }}>
                      <WarningIcon sx={{ color: "yellow", marginRight: "8px" }} />
                      <span>{line}</span>
                    </div>
                  </>
                );
              }
              return null; // skip anything else
            })}
        </div>
      </Drawer>
    </>
  )
}

export default App
